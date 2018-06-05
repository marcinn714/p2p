//
// Created by marcin on 16.05.18.
//

#ifndef TIN_TCPMAINSERVICE_H
#define TIN_TCPMAINSERVICE_H


#include "../commands/Command.hpp"
#include <cstdlib>
#include <pthread.h>
#include <string>
#include <unistd.h>
#include "../../messages/InfoMessage.h"
#include "../fileTables/FilesTableReceive.h"
#include "../files/ReceiveFileTcp.h"
#include "../../netCommunication/TcpCommunication.h"

class TcpMainService: public Command
{
public:
    TcpMainService() {tcpCommunication = new TcpCommunication();}
    virtual ~TcpMainService() = default;

    void execute(void);
    bool reqSeparateThread(void) {	return true; };

private:
    Command * getCommand(size_t opcode, int socketFd, struct in_addr requestingIp);
    void tcpServiceLoop(void);
    TcpCommunication * tcpCommunication;
};


#endif //TIN_TCPMAINSERVICE_H
