//
// Created by marcin on 17.05.18.
//

#include "GetFile.h"
#include "../threads/NetMainThread.h"

void GetFile::execute() {
    if (NetMainThread::getNodeInfo() == nullptr)
        return;
    InfoMessage* msg = new InfoMessage(13, fileName);

    int numberToAdd = 30 - fileName.length();
    if (numberToAdd != 0) {
        fileName.append(numberToAdd, 0);
    }

    if (!NetMainThread::getNodeInfo()->containsRemoteFile(fileName)) {
        std::cout << "No such file in network" << std::endl;
        return;
    }

    udpCommunication->sendInfoMsgUDP(msg, NetMainThread::getNodeInfo()->getFileOwner(fileName), NetMainThread::port);
    delete msg;
}