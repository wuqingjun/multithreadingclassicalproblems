#pragma once
#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>
#include <atomic>
using namespace std;



class TwoThreasPrintingNaturalNumbersLockFree
{
private:
	atomic_int m_count;
	int m_maxCount;

public:
	static void Even(atomic_int &count, int maxCount) {
		while (count < maxCount)
		{
			for (int curr = count; curr % 2 != 0 || !count.compare_exchange_weak(curr, curr + 1); )
			{
				cout << curr << endl;
				curr = count;
			}
		}
	}

	static void Odd(atomic_int &count, int maxCount) {
		while (count < maxCount)
		{
			for (int curr = count; curr % 2 != 1 || !count.compare_exchange_weak(curr, curr + 1); curr = count)
			{
				cout << curr << endl;
				curr = count;
			}
		}
	}


	TwoThreasPrintingNaturalNumbersLockFree(int maxCount) : m_count(0), m_maxCount(maxCount) {}

	void createThreads()
	{
		thread thread0(TwoThreasPrintingNaturalNumbersLockFree::Even, ref(m_count), m_maxCount);
		thread thread1(TwoThreasPrintingNaturalNumbersLockFree::Odd, ref(m_count), m_maxCount);

		thread0.join();
		thread1.join();
	}
};