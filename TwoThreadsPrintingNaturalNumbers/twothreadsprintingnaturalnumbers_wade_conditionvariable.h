#pragma once
#include <mutex>
#include <condition_variable>
#include <thread>
using namespace std;


void Even(int &count, mutex &m, condition_variable &cv, int maxCount) {
	while (count < maxCount)
	{
		unique_lock<mutex> lock(m);

		while (count % 2 != 0)
		{
			cv.wait(lock);
		}
		cout << count << endl;
		++count;
		cv.notify_one();
	}
}

void Odd(int &count, mutex &m, condition_variable &cv, int maxCount) {
	while (count < maxCount)
	{
		unique_lock<mutex> lock(m);

		while (count % 2 != 1)
		{
			cv.wait(lock);
		}
		cout << count << endl;
		++count;
		cv.notify_one();
	}
}


class TwoThreasPrintingNaturalNumbers
{
private:
	int m_count;
	int m_maxCount;
	mutex m_mtx;
	condition_variable m_cv;
	
	
public:
	TwoThreasPrintingNaturalNumbers(int maxCount) : m_count(0), m_maxCount(maxCount) {}

	void createThreads()
	{
		thread thread0(Even, ref(m_count), ref(m_mtx), ref(m_cv), m_maxCount);
		thread thread1(Odd, ref(m_count), ref(m_mtx), ref(m_cv), m_maxCount);

		thread0.join();
		thread1.join();
	}
};