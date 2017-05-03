#pragma once
#include "common.h"

//#define DEBUG_LQMutexLocker

/*!
 * \class LQMutexLocker
 *
 * \brief ������
 *	1.ֻ��һ��Lock()ʱ������һ��UnLock()�����ٽ�����ֻ����һ���߳�ͨ����
 *	2.���ж��Lock()ʱ����Ҫ��ͬ������UnLock()�����̲߳��ܳ��ٽ���
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

