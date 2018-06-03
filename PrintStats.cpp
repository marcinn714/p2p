//
// Created by marcin on 18.05.18.
//

#include <iostream>
#include "PrintStats.h"
#include "netCommunication/NetUtils.h"
#include "NetMainThread.h"


void PrintStats::execute(void)
{
    if (NetMainThread::getNodeInfo() == nullptr)
        return;
    NodeInfo * nodeInfo = NetMainThread::getNodeInfo();
    std::cout << "\nNetwork statistics: "<< std::endl;
    for (auto addr : nodeInfo->getAllNodes()) {
        std::cout << addr << std::endl;
    }
}