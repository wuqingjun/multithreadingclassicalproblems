#pragma once
#include <mutex>
#include <string>
#include <iostream>
#include <thread>
#include <vector>
#include <condition_variable>
using namespace std;

/*
	The first reader - writer problem: Reader Preference
*/

class ReaderWriterProblemI
{
private:
	string m_Content;
	mutex m_Read;
	mutex m_Write;
	condition_variable m_cvWriter;
	int m_nReaderCount;
public:

	int getReaderCount()
	{
		return m_nReaderCount;
	}

	ReaderWriterProblemI(int nReaders): m_nReaderCount(0)
	{
		vector<thread> readers;
		for (int i = 0; i < nReaders; ++i)
		{
			readers.push_back(thread(ReaderWriterProblemI::Read, this));
		}

		thread writer = thread(ReaderWriterProblemI::Write, this);

		for (auto &t : readers)
		{
			t.join();
		}
		writer.join();
	}

	static void Read(ReaderWriterProblemI *rwp)
	{
		string curr;
		while (rwp->m_Content.length() < 200)
		{
			{
				lock_guard<mutex> lock(rwp->m_Read);
				++rwp->m_nReaderCount;
			}

			curr += rwp->m_Content;

			int time = std::rand() % 1;
			this_thread::sleep_for(chrono::microseconds(time));

			{
				lock_guard<mutex> lock(rwp->m_Read);
				if (--rwp->m_nReaderCount)
					rwp->m_cvWriter.notify_one();
			}
		}
		cout << endl  << this_thread::get_id() << curr << endl;
	}

	static void Write(ReaderWriterProblemI *rwp)
	{
		while (rwp->m_Content.length() < 200)
		{
			unique_lock<mutex> lock(rwp->m_Read);

			rwp->m_cvWriter.wait(lock, [rwp] {return rwp->getReaderCount() == 0; });

			int time = std::rand() % 100;
			rwp->m_Content += " I am writing" + to_string(time);
			
			this_thread::sleep_for(chrono::microseconds(time));
		}
	}
};