//
// Created by marcin on 18.05.18.
//

#include "Leave.h"
#include "NetMainThread.h"

void Leave::execute(void) {
    if (NetMainThread::getNodeInfo() == nullptr)
        return;

    InfoMessage* msg = new InfoMessage(11);
    udpCommunication->sendBroadcastInfoMsgUDP(msg, NetMainThread::port);
    delete msg;
}