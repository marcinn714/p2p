//
// Created by marcin on 05.06.18.
//

#include "AddFile.h"

const std::string AddFile::LOCATION = "resources/";


void AddFile::execute() {
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