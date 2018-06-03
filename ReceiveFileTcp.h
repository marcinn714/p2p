//
// Created by marcin on 16.05.18.
//

#ifndef RECEIVEFILETCP_H_
#define RECEIVEFILETCP_H_

#include "Command.hpp"
#include <cstdlib>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "NetMainThread.h"
#include "netCommunication/TcpCommunication.h"

class ReceiveFileTcp: public Command
{
public:
    ReceiveFileTcp(int _socket) : socket(_socket) {tcpCommunication = new TcpCommunication();};

    virtual ~ReceiveFileTcp() {};
    void execute(void);
    bool reqSeparateThread(void) {	return true; }

private:
    int socket;
    TcpCommunication *tcpCommunication;
};

#endif /* RECEIVEFILETCP_H_ */

