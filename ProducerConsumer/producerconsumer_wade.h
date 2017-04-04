#pragma once

/*
	a simple implmentation of Producer Consumer using condition variable
*/

#include <mutex>
#include <condition_variable>
#include <vector>
using namespace std;

template<class T, size_t n = 10>
class CProducerConsumer
{
private:
	vector<T> mBuffer;
	int pos;
	int nSize;
	mutex mtx;
	condition_variable cvFull;
	condition_variable cvEmpty;

public: 
	CProducerConsumer() : mBuffer(n), nSize(0), pos(0) {}

	void Producer()
	{
		while (true)
		{
			T t;
			lock_guard<mutex> lock(mtx);
			cvFull.wait(lock, nSize != n);

			mBuffer[pos] = T;
			pos = (pos + 1) % n;
			++nSize;
			cvEmpty.notify_one();
		}
	}

	void Consumer()
	{
		while (true)
		{
			lock_guard<mutex> lock(mtx);
			cvEmpty.wait(lock, nSize != 0);
			T t = mBuffer[pos];
			pos = (pos - 1 + n) % n;
			--nSize;
			cvFull.notify_one();
		}
	}
};