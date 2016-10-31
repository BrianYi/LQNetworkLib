#pragma once
#include <iostream>
#include <string>
using namespace std;

/* ���Ͷ��� */
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

typedef string IP;
typedef unsigned int Port;
typedef int SocketID;

/* ö�ٶ��� */
enum IOType
{
	BLOCKING = 1,	// ����
	NOBLOCKING		// ������
};