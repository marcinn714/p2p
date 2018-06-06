#ifndef SRC_SENDFILETCP_H_
#define SRC_SENDFILETCP_H_

#include <netinet/in.h>
#include "../commands/Command.hpp"
#include "../../messages/InfoMessage.h"

class SendFileTcp: public Command {
public:
    SendFileTcp(InfoMessage _msg, struct in_addr _ip) : msg(_msg){ip = _ip;}
    SendFileTcp(InfoMessage _msg) : msg(_msg) {}
    virtual ~SendFileTcp() {}

    void execute();
    bool reqSeparateThread() {return true;}
private:
    InfoMessage msg;
    struct in_addr ip;
};

#endif /* SRC_SENDFILETCP_H_ */
