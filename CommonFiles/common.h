/********************************************************************
	����:	2016/12/14 11:06:52
	�ļ���:	common.h
	����:	BrianYi
	
	��;:	����ͷ�ļ������ڶ��峣��ö�ٵȵ�ȫ��ʹ��
*********************************************************************/
#pragma once

#include <winsock2.h>
/*#include <intsafe.h>*/
#include <iostream>
#include <string>
using namespace std;

/* printf or scanf �еĲ��� */
#define _S32_ "%ld"
#define _U32_ "%lu"
#define _S64_ "%I64d"
#define _U64_ "%I64u"

/* ���Ͷ��� */
#ifdef WIN32
typedef unsigned char		UInt8;
typedef signed char			SInt8;
typedef unsigned short		UInt16;
typedef signed short		SInt16;
typedef unsigned long		UInt32;
typedef signed long			SInt32;
typedef signed long long	SInt64;
typedef unsigned long long	UInt64;
typedef float				Float32;
typedef double				Float64;
typedef UInt8				Bool8;
typedef UInt16				Bool16;
#endif

typedef string IP;
typedef unsigned int Port;
typedef int SocketID;

/* ö�ٶ��� */
enum LQ_IOType
{
    lqIOTypeBlocking = 1,	// ����
    lqIOTypeNoBlocking	// ������
};

enum IOType
{
    Blocking = 0,
    NonBlocking = 1
};

const UInt32 RECV_BUF_SIZE = 10 * 1024u;
const UInt32 SEND_BUF_SIZE = 10 * 1024u;
const SInt32 MAX_CONNECTION_NUM = 32;