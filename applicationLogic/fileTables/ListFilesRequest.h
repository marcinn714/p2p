//
// Created by marcin on 18.05.18.
//

#ifndef LISTFILESREQUEST_H_
#define LISTFILESREQUEST_H_

#include "../commands/Command.hpp"
#include "../../messages/InfoMessage.h"
#include "../threads/NetMainThread.h"
#include "../../messages/InfoMessage.h"
#include "../threads/NetMainThread.h"
#include "../Node/NodeInfo.h"
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

    void execute();
    bool reqSeparateThread() {	return true;	};
private:
    UdpCommunication * udpCommunication;
};

#endif /* LISTFILESREQUEST_H_ */

