//
// Created by marcin on 17.05.18.
//

#ifndef SRC_GETFILE_H_
#define SRC_GETFILE_H_

#include "../commands/Command.hpp"
#include "../../netCommunication/UdpCommunication.h"
#include <string>


class GetFile: public Command {
public:
    GetFile(std::string _fileName) : fileName(_fileName) {
        udpCommunication = new UdpCommunication();
    }
    virtual ~GetFile() {delete udpCommunication;}

    void execute();
    bool reqSeparateThread() {return false;}
private:
    std::string fileName;
    UdpCommunication * udpCommunication;
};

#endif /* SRC_GETFILE_H_ */
