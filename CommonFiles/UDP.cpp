#include "UDP.h"

UDP::UDP():CommonSocket(SOCK_DGRAM, IPPROTO_UDP)
{
}


// UDP::UDP(IOType inIOType): CommonSocket(SOCK_DGRAM, inIOType)
// {
// }

UDP::UDP(const UDP& inUDP) :CommonSocket(SOCK_DGRAM, IPPROTO_UDP)
{
    *this = inUDP;
}

UDP::~UDP()
{
}

void UDP::listen_on_port( const UInt16& inPort )
{
	if (!this->m_opened)
		this->open();

	if (!this->m_binded)
	{
		CommonSocket::bind_to_port(inPort);
	}
}

SInt32 UDP::send(const Address& inAddress, const char* inContent, const size_t& inSize)
{
	if (!this->m_opened)
		this->open();

	if (inSize > SEND_BUF_SIZE)
	{
		printf("Send buffer overflow!\n");
		return -1;
	}

	SInt32 sentBytes = ::sendto(this->m_socketID, inContent, inSize, 0, (const sockaddr*)&inAddress, sizeof(struct sockaddr));
	if (sentBytes == -1)
	{
		printf("[send] with %s:%u cannot finish!\n", inAddress.getIP().c_str(), inAddress.getPort());
	}
	return sentBytes;
}

SInt32 UDP::send(const std::string& inIP, const UInt16& inPort, const char* inContent, const size_t& inSize)
{
    if (!this->m_opened)
        this->open();

    if (inSize > SEND_BUF_SIZE)
    {
        printf("Send buffer overflow!\n");
        return -1;
    }

    Address address(inIP, inPort);
    SInt32 sentBytes = ::sendto(this->m_socketID, inContent, inSize, 0, (const sockaddr*)&address, sizeof(struct sockaddr));
    if (sentBytes == -1)
    {
        printf("[send] with %s:%u cannot finish!\n", inIP.c_str(), inPort);
    }
    return sentBytes;
}

SInt32 UDP::receive(char* outContent, const size_t& inSize, IOType inIOType)
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

    SInt32 size = sizeof(struct sockaddr);
    SInt32 receivedBytes = ::recvfrom(this->m_socketID, outContent, inSize, 0, NULL, NULL);
    return receivedBytes;
}

SInt32 UDP::receive(char* outContent, const size_t& inSize, Address& outAddress, IOType inIOType)
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

    int size = sizeof(struct sockaddr);
    SInt32 receivedBytes = ::recvfrom(this->m_socketID, outContent, inSize, 0, (struct sockaddr*)&outAddress, &size);
    return receivedBytes;
}

SInt32 UDP::receive(char* outContent, const size_t& inSize, std::string& outIP, UInt16& outPort, IOType inIOType)
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

    Address address;
    int size = sizeof(struct sockaddr);
    SInt32 receivedBytes = ::recvfrom(this->m_socketID, outContent, inSize, 0, (struct sockaddr*)&address, &size);
    outIP = address.getIP();
    outPort = address.getPort();
    return receivedBytes;
}
