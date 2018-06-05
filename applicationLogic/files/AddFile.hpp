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

    void execute(void) {
        std::ifstream file(LOCATION + fileName.c_str());
        if (!file.is_open()) {
            std::cout << "There is no such file in working directory" << std::endl;
            return;
        }
        NodeInfo* nodeInfo = NetMainThread::getNodeInfo();
        if (nodeInfo != nullptr) {
            nodeInfo->addLocalFile(fileName);
        }
        else {
            std::cout << "Couldn't add new file" << std::endl;
            return;
        }
        std::cout << "Successfully added file" << std::endl;
    }

    bool reqSeparateThread(void) {return true;}

    static const std::string LOCATION;
private:
    std::string fileName;
};

const std::string AddFile::LOCATION = "resources/";

#endif /* ADDNODE_H_ */
