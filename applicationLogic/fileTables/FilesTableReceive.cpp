//
// Created by marcin on 16.05.18.
//

#include "FilesTableReceive.h"
#include "../threads/NetMainThread.h"
#include <iostream>

void FilesTableReceive::execute()
{
    const unsigned bufSize = 25*30; // 32 is size of fileName (string)
    char buf[bufSize];
    int readBytes;
    std::string fileName;

    do {
        memset(buf, 0, sizeof(buf));
        if ((readBytes = tcpCommunication->readData(socket,buf, bufSize)) == -1)
            perror("reading stream message");
        if (readBytes != 0)
        {
                for(unsigned i = 0; i < (unsigned)readBytes/30; ++i)
                {
                    fileName.assign(&buf[i*30], 30);
                    fileName = trim(fileName);
                    std::cout<<"File name - ower: "
                             << fileName <<  " - " << NetUtils::netIpToStringIp(sendingIp)<< std::endl;
                    NetMainThread::getNodeInfo()->addFileToFilesInNetwork(fileName, sendingIp);
                }
        }
    } while (readBytes != 0);
    close(socket);
}


std::string FilesTableReceive::trim(std::string str) {
    char c = 0;
    int strBegin = str.find_first_not_of(c);
    return str.substr(strBegin).append(strBegin, 0);
}