//
// Created by marcin on 17.05.18.
//

#include "GetFile.h"
#include "NetMainThread.h"

void GetFile::execute(void) {
    if (NetMainThread::getNodeInfo() == nullptr)
        return;
    InfoMessage* msg = new InfoMessage(103, param);

    int numberToAdd = 32 - param.length();
    if (numberToAdd != 0) {
        param.append(numberToAdd, 0);
    }

    if (!NetMainThread::getNodeInfo()->containsRemoteFile(param)) {
        std::cout << "No such file in network" << std::endl;
        return;
    }


    udpCommunication->sendInfoMsgUDP(msg, NetMainThread::getNodeInfo()->getFileOwner(param), NetMainThread::port);
    delete msg;
}