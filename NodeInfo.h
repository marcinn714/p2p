//
// Created by marcin on 15.05.18.
//

#ifndef TIN_NODEINFO_H
#define TIN_NODEINFO_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <set>
#include <string>
#include <map>
#include <arpa/inet.h>

class NodeInfo {
private:
    std::set<std::string> files;
    std::set<std::string> nodesInNetwork;
    std::map<std::string,struct in_addr> filesInNetwork;
    bool connected;

public:
    NodeInfo():  connected(true){ };

    void addLocalFile(std::string fileName);
    void removeLocalFile(std::string fileName);
    bool containsLocalFile(std::string fileName);

    void addNewNode(struct in_addr ip);
    void removeNode(struct in_addr ip);
    bool containsRemoteFile(std::string filaName);

    void addFileToFilesInNetwork(std::string fileName, struct in_addr ip);
    void resetFilesInNetwork();

    bool isConnected(void)	{return connected;}

    struct in_addr getFileOwner(std::string);

    std::set<std::string>  getAllNodes() { return nodesInNetwork;}
    std::set<std::string> getAllFiles() { return files;}
};


#endif //TIN_NODEINFO_H
