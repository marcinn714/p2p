//
// Created by marcin on 16.05.18.
//

#include "TcpMainService.h"
#include "FilesTableReceive.h"


Command * TcpMainService::getCommand(size_t opcode, int socketFd, struct in_addr sendingIp)
{
    Command * command = nullptr;
    switch(opcode){
        case 31: //get file
            command = new ReceiveFileTcp(socketFd);
            break;
        case 30: //get local files table
            command = new FilesTableReceive(socketFd, sendingIp);
            break;
        default:
            break;
    }
    return command;
}

void TcpMainService::tcpServiceLoop(void)
{
    tcpCommunication->createAndConfigureSocket();

    Command * command;
    int msgsock, opcode;
    struct sockaddr_in client;
    while (true) {
        if ((opcode = tcpCommunication->receiveOpcode(&msgsock, &client)) != 0) {
            command = getCommand(opcode, msgsock, client.sin_addr);
            if(command->reqSeparateThread())
            {
                pthread_t thread;
                pthread_create(&thread, NULL, Command::commandExeWrapper, static_cast<void *>(command));
                pthread_detach(thread);
            }
            else
            {
                command->execute();
                delete command;
            }
        }
    }
}

void TcpMainService::execute(void)
{
    tcpServiceLoop();
}