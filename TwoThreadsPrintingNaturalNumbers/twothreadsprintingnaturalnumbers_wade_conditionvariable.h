#pragma once
#include <mutex>
#include <condition_variable>
#include <thread>
using namespace std;


class TwoThreasPrintingNaturalNumbers
{
private:
	int m_count;
	mutex m_mtx;
	condition_variable m_cv;

public:
	void createThreads(int maxCount)
	{
		thread thread0([](int &count, mutex &m, condition_variable &cv) {
			while (true)
			{
				lock_guard<mutex> lock(m);

				cv.wait(m, [] {return count % 2 == 0; });
				++count;
				cv.notify_one();
			}
		});

		thread thread1(int &count, mutex &m, condition_variable &cv) {
			while (true)
			{
				lock_guard<mutex> lock(m);

				cv.wait(m, [] {return count % 2 == 1; });
				++count;
				cv.notify_one();
			}
		});
	}
};