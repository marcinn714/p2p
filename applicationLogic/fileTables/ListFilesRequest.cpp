//
// Created by marcin on 18.05.18.
//

#include "ListFilesRequest.h"


void ListFilesRequest::execute()
{
    if (NetMainThread::getNodeInfo() == nullptr)
        return;

    NetMainThread::getNodeInfo()->resetFilesInNetwork();

    InfoMessage *msg = new InfoMessage(12);
    NodeInfo * nInfo = NetMainThread::getNodeInfo();
    for(auto addr : nInfo->getAllNodes()) {
        udpCommunication->sendInfoMsgUDP(msg, NetUtils::stringIpToNetIp(addr), NetMainThread::port);
    }
}
