//
// Created by marcin on 18.05.18.
//
#ifndef SRC_LEAVE_H_
#define SRC_LEAVE_H_

#include "Command.hpp"
#include "netCommunication/UdpCommunication.h"

class Leave: public Command {
public:
    Leave() { udpCommunication = new UdpCommunication();}
    virtual ~Leave() {delete udpCommunication;}

    void execute(void);
    bool reqSeparateThread(void) {return false;}

private:
    UdpCommunication *udpCommunication;
};

#endif /* SRC_LEAVE_H_ */
