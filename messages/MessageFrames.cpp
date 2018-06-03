//
// Created by marcin on 15.05.18.
//

#include "MessageFrames.h"
#include <string.h>
#include <string>


InfoMessage::InfoMessage(char _opcode, std::string fileName)
{
    opcode = _opcode;
    strncpy(hash, fileName.c_str(), FILE_NAME_SIZE);
}

InfoMessage::InfoMessage(char _opcode) {
    opcode = _opcode;
}



InfoMessage::InfoMessage(const InfoMessage & other)
{
    opcode = other.opcode;
    strncpy(hash, other.hash, FILE_NAME_SIZE);
}


char* InfoMessage::converToByte() {
    char * buf = new char[32];
    buf[0] = opcode;
    strcpy(&buf[1], hash);
    return buf;
}

void InfoMessage::fillInfoMessage(char *buf) {
    opcode = buf[0];
    strcpy(hash, &buf[1]);
}