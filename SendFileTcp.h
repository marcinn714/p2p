#ifndef SRC_SENDFILETCP_H_
#define SRC_SENDFILETCP_H_

#include <netinet/in.h>
#include "Command.hpp"
#include "messages/MessageFrames.h"

class SendFileTcp: public Command {
public:
    SendFileTcp(InfoMessage _msg, struct in_addr _ip) : msg(_msg), noMutex(false){ip = _ip;}
    SendFileTcp(InfoMessage _msg, bool _noMutex) : msg(_msg), noMutex(_noMutex) {}
    virtual ~SendFileTcp() {}

    void execute(void);
    bool reqSeparateThread(void) {return true;}
private:
    InfoMessage msg;
    struct in_addr ip;
    bool noMutex;
};

#endif /* SRC_SENDFILETCP_H_ */
