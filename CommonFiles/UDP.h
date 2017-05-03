/********************************************************************
	日期:	2016/12/14 11:05:46
	文件名:	UDP.h
	作者:	BrianYi
	
	用途:	UDP连接的实现
*********************************************************************/
#pragma once
#include "CommonSocket.h"

LQ_BEGIN_NAMESPACE_NETWORK

class LQ_DECL_EXPORT UDP :
    public CommonSocket
{
public:
    UDP();
    UDP(const UDP& inUDP);
    ~UDP();
	void listen_on_port(const UInt16& inPort);
	SInt32 send(const Address& inAddress, const char* inContent, const size_t& inSize);
    SInt32 send(const std::string& inIP, const UInt16& inPort, const char* inContent, const size_t& inSize);
    SInt32 receive(char* outContent, const size_t& inSize, IOType inIOType = Blocking);
    SInt32 receive(char* outContent, const size_t& inSize, Address& outAddress, IOType inIOType = Blocking);
    SInt32 receive(char* outContent, const size_t& inSize, std::string& outIP, UInt16& outPort, IOType inIOType = Blocking);
};

LQ_END_NAMESPACE_NETWORK