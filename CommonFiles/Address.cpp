#include "Address.h"

LQ_BEGIN_NAMESPACE_NETWORK

Address::Address()
{
    _address("0.0.0.0", 0);
}


Address::Address(const UInt16& inPort)
{
    _address("0.0.0.0", inPort);
}

Address::Address(const std::string& inIP, const UInt16& inPort)
{
    _address(inIP, inPort);
}

Address::Address(struct sockaddr_in inSockAddr)
{
    _address(::inet_ntoa(inSockAddr.sin_addr), inSockAddr.sin_port);
}

Address::~Address()
{
}

std::string Address::getIP() const
{
    return ::inet_ntoa(this->sin_addr);
}

void Address::setIP(const std::string& inIP)
{
    ULONG address = ::inet_addr(inIP.c_str());
    if (address == INADDR_NONE)
    {
        printf("Invalid ip address!\n");
    }
    else
    {
        this->sin_addr.s_addr = address;
    }
}

UInt16 Address::getPort() const
{
    return ntohs(this->sin_port);
}

void Address::setPort(const UInt16& inPort)
{
    this->sin_port = htons(inPort);
}

void Address::_address(const std::string& inIP, const UInt16& inPort)
{
    this->sin_family = AF_INET;
    this->setIP(inIP);
    this->setPort(inPort);
}

LQ_END_NAMESPACE_NETWORK