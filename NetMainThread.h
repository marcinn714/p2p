//
// Created by marcin on 15.05.18.
//

#ifndef TIN_NETMAINTHREAD_H
#define TIN_NETMAINTHREAD_H
#include "Command.hpp"
#include "NodeInfo.h"
#include <string>
#include "netCommunication/NetUtils.h"

#include "messages/MessageFrames.h"
#include "netCommunication/NetUtils.h"
#include "TcpMainService.h"
#include "FilesTableSend.h"
#include "netCommunication/UdpCommunication.h"

class NetMainThread: public Command
{
public:
    static NodeInfo * nodeInfo;
    static const unsigned port = 8888;
    static const unsigned joinNetworkPort = 8889;
    static const unsigned maxTimeToJoinP2P = 5;


    NetMainThread();
    virtual ~NetMainThread() { delete nodeInfo; delete udpCommunication; }

    static NodeInfo * getNodeInfo(void);
    void execute(void);
    bool reqSeparateThread(void) {return true;}
    int init(void);
    void buildNetwork(void);
    void receiveNetworkMessages(void);
    void joinNetwork(InfoMessage * req);

private:
    struct sockaddr_in socketAddrIn;
    pthread_t tcpThread;
    bool firstNode;
    UdpCommunication * udpCommunication;
};


#endif //TIN_NETMAINTHREAD_H
