//
// Created by marcin on 15.05.18.
//

#include <iostream>
#include "NodeInfo.h"
#include "netCommunication/NetUtils.h"

void NodeInfo::addLocalFile(std::string fileName){
    files.insert(fileName);
}

void NodeInfo::removeLocalFile(std::string fileName) {
    files.erase(fileName);
}

void NodeInfo::addNewNode(struct in_addr ip) {
    nodesInNetwork.insert(NetUtils::netIpToStringIp(ip));
}

void NodeInfo::removeNode(struct in_addr ip)
{
    nodesInNetwork.erase(NetUtils::netIpToStringIp(ip));
}

void NodeInfo::addFileToFilesInNetwork(std::string fileName, struct in_addr ip) {
    filesInNetwork.insert(std::pair<std::string,struct in_addr>(fileName,ip));
}

void NodeInfo::resetFilesInNetwork() {
    filesInNetwork.clear();
}

struct in_addr NodeInfo::getFileOwner(std::string fileName) {
    std::map<std::string,struct in_addr>::iterator it = filesInNetwork.find(fileName);

    return it->second;
}

bool NodeInfo::containsLocalFile(std::string fileName) {
    return files.find(fileName) != files.end();
}

bool NodeInfo::containsRemoteFile(std::string fileName) {
    return filesInNetwork.find(fileName) != filesInNetwork.end();
}