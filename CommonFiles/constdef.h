#pragma once
#include <iostream>
#include <string>
using namespace std;

/* 类型定义 */
typedef string IP;
typedef unsigned int Port;
typedef int SocketID;

/* 枚举定义 */
enum IOType
{
	BLOCKING = 1,	// 阻塞
	NOBLOCKING		// 非阻塞
};