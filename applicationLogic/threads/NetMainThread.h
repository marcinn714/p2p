//
// Created by marcin on 15.05.18.
//

#ifndef TIN_NETMAINTHREAD_H
#define TIN_NETMAINTHREAD_H
#include "../commands/Command.hpp"
#include "../Node/NodeInfo.h"
#include <string>
#include "../../netCommunication/NetUtils.h"

#include "../../messages/InfoMessage.h"
#include "../../netCommunication/NetUtils.h"
#include "TcpMainService.h"
#include "../fileTables/FilesTableSend.h"
#include "../../netCommunication/UdpCommunication.h"

class NetMainThread: public Command
{
public:
    static NodeInfo * nodeInfo;
    static const unsigned port = 8888;
    static const unsigned joinNetworkPort = 8889;
    static const unsigned maxTimeToJoinP2P = 5;


    NetMainThread();
    virtual ~NetMainThread() { delete nodeInfo; delete udpCommunication; }

    static NodeInfo * getNodeInfo();
    void execute();
    bool reqSeparateThread() {return true;}
    int init();
    void buildNetwork();
    void receiveNetworkMessages();
    void joinNetwork(InfoMessage * req);

private:
    struct sockaddr_in socketAddrIn;
    pthread_t tcpThread;
    bool firstNode;
    UdpCommunication * udpCommunication;
};


#endif //TIN_NETMAINTHREAD_H
