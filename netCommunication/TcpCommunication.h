//
// Created by marcin on 27.05.18.
//

#ifndef TINN_TCPCOMMUNICATION_H
#define TINN_TCPCOMMUNICATION_H

#include <string>
#include <netinet/in.h>
#include <cstdlib>
#include <pthread.h>
#include <string>
#include <unistd.h>

class TcpCommunication {
public:
    static bool sendFileTCP(std::string fileName, std::string* stringFile, struct in_addr ip);
    char receiveOpcode(int  *mgsock, struct sockaddr_in *client);
    void createAndConfigureSocket();
    ssize_t readData(int socket, char *buf, int size);
    bool sendFilesTable(std::string* stringData, struct in_addr targetNodeIP);
    void closeSocket();
private:
    int sock;
};


#endif //TINN_TCPCOMMUNICATION_H
