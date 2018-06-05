//
// Created by marcin on 15.05.18.
//

#ifndef TIN_INFOMESSAGE_H
#define TIN_INFOMESSAGE_H


#include <cstdlib>
#include <string>

class InfoMessage {
public:
    InfoMessage(char opcode = 0);
    InfoMessage(char _opcode, std::string fileName);
    InfoMessage(const InfoMessage & other);

    char * converToByte();
    void fillInfoMessage(char *buf);

    static const int FILE_NAME_SIZE = 33;
    char opcode;
    char hash[FILE_NAME_SIZE];
};



#endif TIN_INFOMESSAGE_H
