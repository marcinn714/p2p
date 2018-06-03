//
// Created by marcin on 15.05.18.
//

#ifndef TIN_NETUTILS_H
#define TIN_NETUTILS_H

#include <string>
#include "../messages/MessageFrames.h"

class NetUtils {
public:
    static std::string getSelfIpAddress(void);
    static std::string getBroadcastAddress(void);
    static struct in_addr getMyIP();
    static struct in_addr stringIpToNetIp(std::string ipStr);
    static std::string netIpToStringIp(struct in_addr ipNet);
};


#endif //TIN_NETUTILS_H
