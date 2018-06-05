//
// Created by marcin on 17.05.18.
//

#include "GetFile.h"
#include "../threads/NetMainThread.h"

void GetFile::execute(void) {
    if (NetMainThread::getNodeInfo() == nullptr)
        return;
    InfoMessage* msg = new InfoMessage(13, param);

    int numberToAdd = 30 - param.length();
    if (numberToAdd != 0) {
        param.append(numberToAdd, 0);
    }

    NodeInfo * n = NetMainThread::getNodeInfo();

    if (!NetMainThread::getNodeInfo()->containsRemoteFile(param)) {
        std::cout << "No such file in network" << std::endl;
        return;
    }


    udpCommunication->sendInfoMsgUDP(msg, NetMainThread::getNodeInfo()->getFileOwner(param), NetMainThread::port);
    delete msg;
}