#pragma once

#include <string>
#include <future>
#include <iostream>
#include <mutex>
#include <condition_variable>
using namespace std;

void WriteToDiskLockFree(string &buff, string &info,  atomic_int &len, int size)
{
	int currLen = len;
	for (; !len.compare_exchange_weak(currLen, len + info.size(), std::memory_order_release, std::memory_order_relaxed); 
		currLen = len);

	for (int i = 0; i < info.size(); ++i)
	{
		buff[currLen + i] = info[i];
	}
	
	int start = 0;
	for (currLen = len, start = buff.end() - currLen - buff.begin(); currLen >= size
		&& !len.compare_exchange_weak(currLen, currLen - size, std::memory_order_release, std::memory_order_relaxed);
		currLen = len, start = buff.end() - currLen - buff.begin()
		);

	cout << buff.substr(start, size) << endl;
}

class LogLockFree
{
private:
	atomic_int m_len;
	int m_size;
	string m_buff;
public:
	LogLockFree(int n) : m_size(n), m_buff(2 * n, '\0'), m_len(0) {}

	int WriteLog(string &info)
	{
		future<void> fu = async(WriteToDiskLockFree, ref(m_buff),
			ref(info), ref(m_len), m_size);

		fu.get();

		return fu._Is_ready();
	}
};