#pragma once

#include <atomic>
#include <cassert>
using namespace std;

class Semaphore
{
private:
	int m_Size;
	atomic_int m_Count;
public:
	Semaphore(int n): m_Count(n), m_Size(n) {}
	void V()
	{
		assert(m_Count <= m_Size);
		for (int n = m_Count; n >= m_Size || !m_Count.compare_exchange_weak(n, n + 1, std::memory_order_release, std::memory_order_relaxed);
			n = m_Count) {
			assert(n <= m_Size);
		}
		assert(m_Count <= m_Size);
	}

	void P()
	{
		assert(m_Count <= m_Size);
		for (int n = m_Count; n <= 0 || !m_Count.compare_exchange_weak(n, n - 1, std::memory_order_release, std::memory_order_relaxed);
			n = m_Count) {
			assert(n <= m_Size);
		}
		assert(m_Count <= m_Size);
	}

	int getCount()
	{
		return m_Count;
	}
};