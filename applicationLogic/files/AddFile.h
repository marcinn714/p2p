//
// Created by marcin on 16.05.18.
//

#ifndef ADDNODE_H_
#define ADDNODE_H_

#include "../commands/Command.hpp"
#include <string>
#include "../../netCommunication/NetUtils.h"
#include "../threads/NetMainThread.h"

class AddFile: public Command
{
public:
    AddFile(std::string _fileName) : fileName(_fileName) {}
    virtual ~AddFile() {}

    void execute(void);

    bool reqSeparateThread(void) {return true;}

    static const std::string LOCATION;
private:
    std::string fileName;
};



#endif /* ADDNODE_H_ */
