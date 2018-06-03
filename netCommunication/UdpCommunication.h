//
// Created by marcin on 27.05.18.
//

#ifndef TINN_UDPCOMMUNICATION_H
#define TINN_UDPCOMMUNICATION_H

#include <string>
#include <netinet/in.h>
#include "../messages/MessageFrames.h"

class UdpCommunication {
public:
    UdpCommunication();
    static bool sendInfoMsgUDP(InfoMessage * msg, struct in_addr nodeAddr, unsigned port);
    bool sendBroadcastInfoMsgUDP(InfoMessage * msg, unsigned port);
    ssize_t receiveInfoMsgUDP(InfoMessage * msg, unsigned port, struct sockaddr_in * commonSocketAddrIn, unsigned timeout = 0);
private:
    std::string broadcastAddress;
};


#endif //TINN_UDPCOMMUNICATION_H
