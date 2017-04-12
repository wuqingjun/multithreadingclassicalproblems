#pragma once

#include <condition_variable>
using namespace std;

namespace SemaphoreImplementedUsingConditionVariable
{
	class Semaphore
	{
	private:
		int m_nSize;
		int m_nCount;
		mutex m_mtx;
		condition_variable m_cv;
	public:
		Semaphore(int size) : m_nSize(size), m_nCount(size) {}
		void P()
		{
			unique_lock<mutex> lock(m_mtx);
			m_cv.wait(lock, [this] {return  this->m_nCount > 0; });
			--m_nCount;
		}
		void V()
		{
			unique_lock<mutex> lock(m_mtx);
			if (m_nCount < m_nSize)
			{
				++m_nCount;
				m_cv.notify_one();
			}
		}

		int getCount() { return m_nCount; }
	};
}