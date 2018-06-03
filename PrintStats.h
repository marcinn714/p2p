//
// Created by marcin on 18.05.18.
//

#ifndef PRINTSTATS_H_
#define PRINTSTATS_H_

#include "Command.hpp"
#include <arpa/inet.h>
#include <functional>

class PrintStats: public Command
{
public:
    PrintStats() = default;
    virtual ~PrintStats() = default;
    void execute(void);
    bool reqSeparateThread(void) { return false; }

private:
    void printNodeInfo(size_t nodeId, struct in_addr *);
};

#endif /* PRINTSTATS_H_ */
