#pragma once
#include "common.h"

//#define DEBUG_LQMutexLocker

/*!
 * \class LQMutexLocker
 *
 * \brief 互斥锁
 *	1.只有一个Lock()时，与下一个UnLock()构成临界区（只允许一个线程通过）
 *	2.当有多个Lock()时，需要相同个数的UnLock()，该线程才能出临界区
 *
 * \author YJZ
 * \date 2016/10/29
 */
class LQMutexLocker
{
public:
	LQMutexLocker();
	~LQMutexLocker();
	void Lock();
	void Unlock();
private:
	void RecursiveLock();
	void RecursiveUnlock();
private:
	CRITICAL_SECTION m_mutex;
	UInt32 m_holderCount;
	DWORD m_holder;
};

