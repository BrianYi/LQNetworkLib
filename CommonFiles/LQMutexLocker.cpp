#include "stdafx.h"
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

void LQMutexLocker::Lock()
{
	this->RecursiveLock();
}

void LQMutexLocker::Unlock()
{
	this->RecursiveUnlock();
}

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
