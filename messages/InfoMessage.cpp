//
// Created by marcin on 15.05.18.
//

#include "InfoMessage.h"
#include <string.h>


InfoMessage::InfoMessage(char _opcode, std::string _fileName)
{
    opcode = _opcode;
    strncpy(fileName, _fileName.c_str(), FILE_NAME_SIZE);
}

InfoMessage::InfoMessage(char _opcode) {
    opcode = _opcode;
}


InfoMessage::InfoMessage(const InfoMessage & other)
{
    opcode = other.opcode;
    strncpy(fileName, other.fileName, FILE_NAME_SIZE);
}

char* InfoMessage::converToByte() {
    char * buf = new char[32];
    buf[0] = opcode;
    strcpy(&buf[1], fileName);
    return buf;
}

void InfoMessage::fillInfoMessage(char *buf) {
    opcode = buf[0];
    strcpy(fileName, &buf[1]);
}