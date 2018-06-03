//
// Created by marcin on 15.05.18.
//

#include "NetMainThread.h"
#include <stdio.h> //printf
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <pthread.h>
#include <iostream>
#include <errno.h>
#include <string>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <sys/uio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdint>
#include <net/if.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include "messages/MessageFrames.h"
#include "SendFileTcp.h"

NodeInfo* NetMainThread::nodeInfo;

NetMainThread::NetMainThread(): tcpThread(0), firstNode(false) {
    udpCommunication = new UdpCommunication();
}



NodeInfo * NetMainThread::getNodeInfo(void){
    return nodeInfo;
}

void NetMainThread::receiveNetworkMessages(void) {
    std::cout << "Net Main Thread's started" << std::endl;
    InfoMessage * msg = new InfoMessage();
    while (udpCommunication->receiveInfoMsgUDP(msg, port, &socketAddrIn)) {
        switch(msg->opcode) {
            case 10: //new node wants to join
            {

                msg->opcode = 20;
//                InfoMessage *msg = new InfoMessage(20);
                udpCommunication->sendInfoMsgUDP(msg, socketAddrIn.sin_addr, joinNetworkPort);
                nodeInfo->addNewNode(socketAddrIn.sin_addr);
                break;
            }
            case 11: //node wants to leave (this node or another)
            {
                nodeInfo->removeNode(socketAddrIn.sin_addr);
                pthread_cancel(tcpThread);
                Command::exitCommand(this);
                break;
            }
            case 12: //other node wants local files table
            {
                pthread_t thread;
                Command * sendFilesTable = new FilesTableSend(socketAddrIn.sin_addr);
                pthread_create(&thread, 0, Command::commandExeWrapper, static_cast<void *>(sendFilesTable));
                pthread_detach(thread);
                break;
            }
            case 13: //other node wants to get file from this node's local files
            {
                pthread_t thread;
                Command* sendFileTcp = new SendFileTcp(*msg, socketAddrIn.sin_addr);
                pthread_create(&thread, NULL, Command::commandExeWrapper, static_cast<void *>(sendFileTcp));
                pthread_detach(thread);
                break;
            }
            case 40: //exceptional situation when more than 1 new nodes want to join simultaneously
            {
                std::cout << "Failed when joining to network" << std::endl;
                pthread_cancel(tcpThread);
                delete this;
                exit(1);
            }
            case 41:
            {
                std::cout << "File no longer available" << std::endl;
            }
            std::cout << "";
        }
    }
    delete msg;
}

void NetMainThread::buildNetwork(void) {
    firstNode = true;
    std::cout << "Didn't receive any response\nStart building new P2P network... ";
    nodeInfo = new NodeInfo();
    InfoMessage * msg = new InfoMessage(40); //if another node's waiting for response
    udpCommunication->sendBroadcastInfoMsgUDP(msg, joinNetworkPort);
    std::cout << "Completed" << std::endl;
    delete msg;
}

void NetMainThread::joinNetwork(InfoMessage * msg) {
    if (msg->opcode == 40) {
        std::cout << "Another node's building P2P network right now" << std::endl;
        Command::exitCommand(this);
    }
    firstNode = false;
    if (msg->opcode == 20) {
        nodeInfo = new NodeInfo();
        nodeInfo->addNewNode(socketAddrIn.sin_addr);
    }

    while((udpCommunication->receiveInfoMsgUDP(msg, joinNetworkPort, &socketAddrIn, 2)) > 0) {
        if (msg->opcode == 20) { //msg about network (cnt, sender id, receiver id)
            nodeInfo->addNewNode(socketAddrIn.sin_addr);
        }
    }
}

int NetMainThread::init(void)
{
    InfoMessage * msg = new InfoMessage(10);
    udpCommunication->sendBroadcastInfoMsgUDP(msg, port);
    std::cout<<"Sent joining to network request" <<std::endl;

    //receive udp socket
    std::cout<<"Waiting for response within " << maxTimeToJoinP2P << " seconds" <<std::endl;
    if (udpCommunication->receiveInfoMsgUDP( msg, joinNetworkPort, &socketAddrIn, maxTimeToJoinP2P) < 0)
        buildNetwork();
    else
        joinNetwork(msg);
    delete msg;
    return 0;
}

void NetMainThread::execute(void)
{
    Command * command;

    if(nodeInfo != nullptr && nodeInfo->isConnected()){
        std::cout<<"Node's already connected to network" << std::endl;
        pthread_exit(NULL);
    }
    init();

    // Create Main tcp listener thread
    command = new TcpMainService();
    pthread_create(&tcpThread, NULL, Command::commandExeWrapper, static_cast<void *>(command));
    pthread_detach(tcpThread);

    receiveNetworkMessages();
}

