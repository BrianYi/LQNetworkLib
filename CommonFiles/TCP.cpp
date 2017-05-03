#include "TCP.h"

LQ_BEGIN_NAMESPACE_NETWORK

TCP::TCP():CommonSocket(SOCK_STREAM, IPPROTO_TCP)
{

}

TCP::TCP(const TCP& inTCP) : CommonSocket(SOCK_STREAM, IPPROTO_TCP)
{
    *this = inTCP;
}

// TCP::TCP( IOType inIOType ):CommonSocket(SOCK_STREAM, inIOType)
// {
// 
// }

TCP::~TCP()
{
}

void TCP::listen_on_port( const UInt16& inPort )
{
	if (!this->m_opened)
		this->open();
	
	if (!this->m_binded)
	{
		CommonSocket::bind_to_port(inPort);
	}

	if (::listen(this->m_socketID, MAX_CONNECTION_NUM) != 0)
	{
		printf("[TCP] listen_on_port error!\n");
		return;
	}
}

SInt32 TCP::connect_to( const Address& inAddress )
{
	if (this->m_binded)
	{
		printf("Socket %u already binded!\n", this->m_socketID);
		return -1;
	}
	if (!this->m_opened)
		this->open();

	SInt32 ret = ::connect(this->m_socketID, (const sockaddr*)&inAddress, sizeof(struct sockaddr));
	if (ret == 0)
	{
		this->m_address = inAddress;
		this->m_binded = TRUE;
	}
	return ret;
}

SInt32 TCP::connect_to( const std::string& inIP, const UInt16& inPort )
{
	if (this->m_binded)
	{
		printf("Socket %u already binded!\n", this->m_socketID);
		return -1;
	}
	if (!this->m_opened)
		this->open();

    Address address(inIP, inPort);
	SInt32 ret = ::connect(this->m_socketID, (const sockaddr*)&address, sizeof(struct sockaddr));
	if (ret == 0)
	{
        this->m_address = address;
        this->m_binded = TRUE;
    }
	return ret;
}

TCP TCP::accept_client(IOType inIOType)
{
    if (this->m_ioType != inIOType)
        this->setIOType(inIOType);

	int size = sizeof(struct sockaddr);
	Address address;
	SOCKET socketID = ::accept(this->m_socketID, (struct sockaddr*)&address, &size);
	TCP client;
	client.m_socketID = socketID;
	client.m_binded = TRUE;
	client.m_opened = TRUE;
	client.m_address = address;
	return client;
}

SInt32 TCP::send( const char* inContent, const size_t& inSize )
{
	if (!this->m_opened)
		this->open();

	if (inSize > SEND_BUF_SIZE)
	{
		printf("Send buffer overflow!\n");
		return -1;
	}

	SInt32 sentBytes = ::send(this->m_socketID, inContent, inSize, 0);
	if (sentBytes == -1)
	{
		printf("[send] with %s:%u cannot finish!\n", this->m_address.getIP().c_str(), this->m_address.getPort());
	}
	return sentBytes;
}

SInt32 TCP::receive( char* outContent, const size_t& inSize, IOType inIOType)
{
	if (!this->m_opened)
		this->open();
	if (!this->m_binded)
	{
		printf("Please first listen on port!\n");
		return -1;
	}

    if (this->m_ioType != inIOType)
        this->setIOType(inIOType);

	SInt32 receivedBytes = ::recv(this->m_socketID, outContent, inSize, 0);
	return receivedBytes;
}

Address TCP::getAddress( void )
{
	return m_address;
}

std::string TCP::getIP( void )
{
	return m_address.getIP();
}

UInt16 TCP::getPort( void )
{
	return m_address.getPort();
}

LQ_END_NAMESPACE_NETWORK