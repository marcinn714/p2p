//
// Created by marcin on 18.05.18.
//

#ifndef LISTFILESREQUEST_H_
#define LISTFILESREQUEST_H_

#include "Command.hpp"
#include "messages/MessageFrames.h"
#include "NetMainThread.h"
#include "messages/MessageFrames.h"
#include "NetMainThread.h"
#include "NodeInfo.h"
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <functional>

class ListFilesRequest: public Command
{
public:
    ListFilesRequest(){udpCommunication = new UdpCommunication();}
    virtual ~ListFilesRequest() = default;

    void execute(void);
    bool reqSeparateThread(void) {	return true;	};
private:
    UdpCommunication * udpCommunication;
};

#endif /* LISTFILESREQUEST_H_ */

