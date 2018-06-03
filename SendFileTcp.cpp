//
// Created by marcin on 18.05.18.
//

#include "SendFileTcp.h"
#include "NetMainThread.h"
#include "netCommunication/TcpCommunication.h"

#include <string>

void SendFileTcp::execute(void) {
    if (!NetMainThread::getNodeInfo()->containsLocalFile(msg.hash)) {
        UdpCommunication::sendInfoMsgUDP(new InfoMessage(401), ip, NetMainThread::port);
        return;
    }


    std::string fileStr;
    std::ifstream file(msg.hash, std::ios::in | std::ios::binary);
    if (!file) {
        UdpCommunication::sendInfoMsgUDP(new InfoMessage(401), ip, NetMainThread::port);
        return;
    }
    file.seekg(0, std::ios::end); //how big is file
    fileStr.reserve(file.tellg());
    file.seekg(0, std::ios::beg);

    fileStr.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()); //copy file to string

    TcpCommunication::sendFileTCP(msg.hash, &fileStr, ip);
}