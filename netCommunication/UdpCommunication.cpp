//
// Created by marcin on 27.05.18.
//

#include <zconf.h>
#include <cstring>
#include <arpa/inet.h>
#include <iostream>
#include "UdpCommunication.h"
#include "NetUtils.h"


UdpCommunication::UdpCommunication() {
    broadcastAddress = NetUtils::getBroadcastAddress();
}

bool UdpCommunication::sendInfoMsgUDP(InfoMessage * msg, struct in_addr nodeAddr, unsigned port) {
    int commonSocketFd;
    struct sockaddr_in commonSocketAddrIn;
    socklen_t slen = sizeof(commonSocketAddrIn);

    //socket
    if ((commonSocketFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        return false;

    int option = 1;
    if (setsockopt(commonSocketFd,SOL_SOCKET,SO_REUSEADDR, &option, sizeof(option)) < 0)
        return false;

    memset((char *) &commonSocketAddrIn, 0, sizeof(commonSocketAddrIn));
    commonSocketAddrIn.sin_family = AF_INET;
    commonSocketAddrIn.sin_port = htons(port);
    commonSocketAddrIn.sin_addr = nodeAddr;


    if (sendto(commonSocketFd, msg->converToByte(), 32, 0, (struct sockaddr*) &commonSocketAddrIn, slen) < 0)
        return false;

    std::cout << "wyslano: " <<  +msg->opcode << std::endl;

    close(commonSocketFd);
    return true;
}

bool UdpCommunication::sendBroadcastInfoMsgUDP(InfoMessage * msg, unsigned port) {
    int commonSocketFd;
    struct sockaddr_in commonSocketAddrIn;
    socklen_t slen = sizeof(commonSocketAddrIn);

    //socket
    if ((commonSocketFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        return false;

    //broadcast
    int broadcast = 1, option = 1;
    if (setsockopt(commonSocketFd,SOL_SOCKET,SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0)
        return false;
    if (setsockopt(commonSocketFd,SOL_SOCKET,SO_REUSEADDR, &option, sizeof(option)) < 0)
        return false;

    memset((char *) &commonSocketAddrIn, 0, sizeof(commonSocketAddrIn)); //wyzerowanie struktury adresu odbiorcy
    commonSocketAddrIn.sin_family = AF_INET;
    commonSocketAddrIn.sin_port = htons(port);

    if (inet_aton(broadcastAddress.c_str() , &commonSocketAddrIn.sin_addr) == 0)//przypisanie adresu odbiorcy (broadcast)
        return false;
    if (sendto(commonSocketFd, msg->converToByte(), 32, 0, (struct sockaddr*) &commonSocketAddrIn, slen) < 0)
        return false;

    std::cout << "wyslano: " <<  +msg->opcode << std::endl;

    close(commonSocketFd);
}

ssize_t UdpCommunication::receiveInfoMsgUDP(InfoMessage *msg, unsigned port, struct sockaddr_in * commonSocketAddrIn ,unsigned int timeout) {
    int commonSocketFd;
    socklen_t slen = sizeof(*commonSocketAddrIn);

    //receive udp socket
    if ((commonSocketFd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        return 0;
    // zero out the structure
    memset((char *) commonSocketAddrIn, 0, sizeof(*commonSocketAddrIn));
    commonSocketAddrIn->sin_family = AF_INET;
    commonSocketAddrIn->sin_port = htons(port);
    commonSocketAddrIn->sin_addr.s_addr = htonl(INADDR_ANY);

    int option = 1;
    if (setsockopt(commonSocketFd,SOL_SOCKET,SO_REUSEADDR, &option, sizeof(option)) < 0)
        return 0;

    if (timeout > 0) {
        //recv first info about network in x secs, otherwise -> new network
        struct timeval tv;
        tv.tv_sec = timeout;
        tv.tv_usec = 0;
        if (setsockopt(commonSocketFd, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0)
            return  0;
    }

    //bind socket to port
    if(bind(commonSocketFd , (struct sockaddr*)commonSocketAddrIn, sizeof(*commonSocketAddrIn) ) < 0){
        return 0;
    }

    ssize_t recv_len;
    char buf[32];
    if ((recv_len = recvfrom(commonSocketFd, buf, 32, 0, (struct sockaddr *) commonSocketAddrIn, &slen)) < 0 && !timeout) {
        return 0;
    }
    msg->fillInfoMessage(buf);
    std::cout << "otrzymano: " <<  +msg->opcode << std::endl;
    close(commonSocketFd);

    return recv_len;
}