//
// Created by marcin on 16.05.18.
//

#include "FilesTableReceive.h"
#include "NetMainThread.h"
#include <iostream>

void FilesTableReceive::execute()
{
    const unsigned bufSize = 25*32; // 32 is size of fileName (string)
    char buf[bufSize];
    int readBytes;
    std::string fileName;

    NetMainThread::getNodeInfo()->resetFilesInNetwork();

    do {
        memset(buf, 0, sizeof(buf));
        if ((readBytes = tcpCommunication->readData(socket,buf, bufSize)) == -1)
            perror("reading stream message");
        if (readBytes != 0)
        {
                for(unsigned i = 0; i < (unsigned)readBytes/32; ++i)
                {
                    fileName.assign(&buf[i*32], 32);
                    std::cout<<"File name - ower: "
                             << fileName <<  " - " << NetUtils::netIpToStringIp(sendingIp)<< std::endl;
                    NetMainThread::getNodeInfo()->addFileToFilesInNetwork(fileName, sendingIp);
                }
        }
    } while (readBytes != 0);
    close(socket);
}
