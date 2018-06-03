//
// Created by marcin on 17.05.18.
//

#ifndef SRC_GETFILE_H_
#define SRC_GETFILE_H_

#include "Command.hpp"
#include "netCommunication/UdpCommunication.h"
#include <string>


class GetFile: public Command {
public:
    GetFile(std::string _param) : param(_param) { udpCommunication = new UdpCommunication();}
    virtual ~GetFile() {}

    void execute(void);
    bool reqSeparateThread(void) {return false;}
private:
    std::string param;
    UdpCommunication * udpCommunication;
};

#endif /* SRC_GETFILE_H_ */
