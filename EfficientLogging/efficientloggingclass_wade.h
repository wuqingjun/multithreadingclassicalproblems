#pragma once

#include <string>
#include <future>
#include <iostream>
#include <mutex>
#include <condition_variable>
using namespace std;

void WriteToDisk(string &buff, string &info, mutex &m, int size)
{
	lock_guard<mutex> lock(m);
	
	if (buff.size() + info.size() <= size)
	{
		buff += info;
	}
	else
	{
		cout << "Writing to Disk :" << buff << endl;
		buff = info;
	}
}

class Log
{
private:
	mutex m_mtx;
	int m_size;
	string m_buff;
public:
	Log(int n): m_size(n) {}

	int WriteLog(string &info)
	{
		future<void> fu = async(WriteToDisk, ref(m_buff),
			ref(info), ref(m_mtx), ref(m_size));

		return fu._Is_ready();
	}
};