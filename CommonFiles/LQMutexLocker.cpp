#include "LQMutexLocker.h"


LQMutexLocker::LQMutexLocker()
{
	::InitializeCriticalSection(&m_mutex);
	m_holder = 0;
	m_holderCount = 0;
}


LQMutexLocker::~LQMutexLocker()
{
	::DeleteCriticalSection(&m_mutex);
}

//************************************
// 函数名:	Lock
// 描述:		锁
// 返回值:	void
// 日期:		2016/10/31
// 作者:		YJZ
// 修改记录:	
//************************************
void LQMutexLocker::Lock()
{
	this->RecursiveLock();
}

//************************************
// 函数名:	Unlock
// 描述:		解锁
// 返回值:	void
// 日期:		2016/10/31
// 作者:		YJZ
// 修改记录:	
//************************************
void LQMutexLocker::Unlock()
{
	this->RecursiveUnlock();
}

//************************************
// 函数名:	RecursiveLock
// 描述:		迭代锁
// 返回值:	void
// 日期:		2016/10/31
// 作者:		YJZ
// 修改记录:	
//************************************
void LQMutexLocker::RecursiveLock()
{
	if (::GetCurrentThreadId() == m_holder)
	{
		m_holderCount++;
#ifdef DEBUG_LQMutexLocker
		printf("holder count = %d\n", m_holderCount);
#endif
		return;
	}
	::EnterCriticalSection(&m_mutex);
	m_holder = ::GetCurrentThreadId();
#ifdef DEBUG_LQMutexLocker
	printf("thread %d enter critical section\n", m_holder);
#endif
	m_holderCount++;
}

//************************************
// 函数名:	RecursiveUnlock
// 描述:		迭代解锁
// 返回值:	void
// 日期:		2016/10/31
// 作者:		YJZ
// 修改记录:	
//************************************
void LQMutexLocker::RecursiveUnlock()
{
	if (::GetCurrentThreadId() != m_holder)
	{
		return;
	}

	m_holderCount--;
#ifdef DEBUG_LQMutexLocker
	printf("holder count = %d\n", m_holderCount);
#endif
	if (m_holderCount == 0)
	{
#ifdef DEBUG_LQMutexLocker
		printf("thread %d leave critical section\n", m_holder);
#endif
		m_holder = 0;
		::LeaveCriticalSection(&m_mutex);
	}
}
