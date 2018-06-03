//
// Created by marcin on 15.05.18.
//

#ifndef TIN_MESSAGEFRAMES_H
#define TIN_MESSAGEFRAMES_H


#include <cstdlib>
#include <string>

class InfoMessage {
public:
    InfoMessage(char opcode = 0);
    InfoMessage(char _opcode, std::string fileName);
    InfoMessage(const InfoMessage & other);
    void fillName();
    char opcode;
    static const int FILE_NAME_SIZE = 31;
    char hash[FILE_NAME_SIZE];
    char * converToByte();
    void fillInfoMessage(char *buf);
};



#endif //TIN_MESSAGEFRAMES_H
