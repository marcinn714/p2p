//
// Created by marcin on 16.05.18.
//

#include "ReceiveFileTcp.h"
#include "AddFile.h"

void ReceiveFileTcp::execute(void)
{
    char buf[1024];
    char fileName[InfoMessage::FILE_NAME_SIZE];

    int readBytes;
    if (tcpCommunication->readData(socket, fileName, InfoMessage::FILE_NAME_SIZE) < 0) //read filename
        perror("reading stream message error");

    std::ofstream newFile(AddFile::LOCATION + fileName, std::ios::out);
    do {
        memset(buf, 0, sizeof(buf));
        if ((readBytes = tcpCommunication->readData(socket, buf, 1024)) < 0)
            perror("reading stream message error");
        if (readBytes != 0)
            newFile.write(buf, readBytes);
    } while (readBytes != 0);

    newFile.close();
    std::cout << "Added new file: " << fileName  << std::endl << std::flush;
    close(socket);
}
