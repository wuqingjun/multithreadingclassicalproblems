#pragma once

#include <atomic>
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
		for (int n = m_Count; n >= m_Size || !m_Count.compare_exchange_weak(n, n + 1, std::memory_order_release, std::memory_order_relaxed);
			n = m_Count) { 	}
	}

	void P()
	{
		for (int n = m_Count; n <= 0 || !m_Count.compare_exchange_weak(n, n + 1, std::memory_order_release, std::memory_order_relaxed);
			n = m_Count) {
		}
	}
};