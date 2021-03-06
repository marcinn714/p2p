//
// Created by marcin on 19.05.18.
//

#include "FilesTableSend.h"
#include "../threads/NetMainThread.h"


#include <cstdint>
#include <net/if.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <functional>

FilesTableSend::FilesTableSend(struct in_addr _targetNodeIP)
{
    targetNodeIP = _targetNodeIP;
    tcpCommunication = new TcpCommunication();
}

void FilesTableSend::insertData(std::string fileName)
{
    int numberToAdd = 30 - fileName.length();
    if (numberToAdd != 0)
        fileName.append(numberToAdd + 1, 0);

    fileTableData << fileName;
}

void FilesTableSend::execute()
{
    NodeInfo * nodeInfo = NetMainThread::getNodeInfo();
    for (auto &file : nodeInfo->getAllFiles()) {
        insertData(file);
    }
    std::string filesData = fileTableData.str();
    tcpCommunication->sendFilesTable(&filesData, targetNodeIP);
}
