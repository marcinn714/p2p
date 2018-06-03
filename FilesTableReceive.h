//
// Created by marcin on 16.05.18.
//

#ifndef FILESTABLERECEIVE_H_
#define FILESTABLERECEIVE_H_

#include "Command.hpp"
#include "netCommunication/TcpCommunication.h"
#include <cstdlib>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>

class FilesTableReceive: public Command
{
public:
    FilesTableReceive( int _socket, struct in_addr ip) : socket(_socket) {
        sendingIp = ip;
        tcpCommunication = new TcpCommunication();
    };

    virtual ~FilesTableReceive() {};

    void execute();
    bool reqSeparateThread(void) {	return true; }

private:
    int socket;
    struct in_addr sendingIp;
    TcpCommunication * tcpCommunication;
};

#endif /* FILESTABLERECEIVE_H_ */

