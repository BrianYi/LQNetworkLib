/********************************************************************
	日期:	2016/12/14 11:06:05
	文件名:	CommonSocket.h
	作者:	BrianYi
	
	用途:	TCP和UDP类的公共基类，用于封装socket处理
*********************************************************************/
#pragma once
#include "common.h"
#include "Address.h"

LQ_BEGIN_NAMESPACE_NETWORK

class LQ_DECL_EXPORT CommonSocket
{
public:
    CommonSocket(SInt32 inSocketType, SInt32 inProtocol, IOType inIOType = Blocking);
    ~CommonSocket();
	void setIOType(IOType inIOType);
    void reuse_addr();
    void no_delay();
    void keep_alive();
    void set_socket_sndbuf_size(UInt32 inNewSize);
    void set_socket_rcvbuf_size(UInt32 inNewSize);
protected:
    void open();
    void close();
    void bind_to_port(const UInt16& inPort);
protected:
    SOCKET m_socketID;
    SInt32 m_socketType;
    SInt32 m_protocol;
    BOOL m_opened;
    BOOL m_binded;
    IOType m_ioType;
private:
    CommonSocket();
    static UInt32 s_num_sockets;
};

LQ_END_NAMESPACE_NETWORK