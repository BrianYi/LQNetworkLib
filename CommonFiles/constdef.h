#pragma once
#include <iostream>
#include <string>
using namespace std;

/* ���Ͷ��� */
typedef string IP;
typedef unsigned int Port;
typedef int SocketID;

/* ö�ٶ��� */
enum IOType
{
	BLOCKING = 1,	// ����
	NOBLOCKING		// ������
};