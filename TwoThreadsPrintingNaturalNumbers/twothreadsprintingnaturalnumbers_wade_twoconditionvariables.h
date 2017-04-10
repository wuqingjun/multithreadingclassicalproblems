#pragma once
#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>
using namespace std;

class TwoThreasPrintingNaturalNumbersTwoVariables
{
public:
	static void printNumber(TwoThreasPrintingNaturalNumbersTwoVariables * t, int expected) {
		while (t->m_count < t->m_maxCount)
		{
			unique_lock<mutex> lock(t->m_mtx);
			t->m_cvs[expected].wait(lock, [t, expected] {return t->m_count % 2 == expected; });
			cout << t->m_count++ << endl;
			t->m_cvs[(expected + 1) % 2].notify_one();
		}
	}
private:
	int m_count;
	int m_maxCount;
	mutex m_mtx;
	vector<condition_variable> m_cvs;


public:
	TwoThreasPrintingNaturalNumbersTwoVariables(int maxCount) : m_count(0), m_maxCount(maxCount), m_cvs(2) {}

	void createThreads()
	{
		thread thread0(printNumber, this, 0);
		thread thread1(printNumber, this, 1);

		thread0.join();
		thread1.join();
		getchar();
	}
};