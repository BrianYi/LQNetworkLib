#pragma once
#include "common.h"
#include <string>

class LQ_DECL_EXPORT Address : public sockaddr_in
{
public:
    Address();
    Address(const UInt16& inPort);
    Address(const std::string& inIP, const UInt16& inPort);
    Address(struct sockaddr_in inSockAddr);
    ~Address();
    std::string getIP() const;
    void setIP(const std::string& inIP);
    UInt16 getPort() const;
    void setPort(const UInt16& inPort);
private:
    void _address(const std::string& inIP, const UInt16& inPort);
};

