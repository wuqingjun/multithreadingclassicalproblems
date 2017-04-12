#pragma once
#include <mutex>
#include <string>
#include <iostream>
#include <thread>
#include <vector>
#include <condition_variable>
#include "../SemaphoreImplementedUsingConditionVariable/semaphoreimplementedusingconditionvariable_wade.h"
using namespace std;
using namespace SemaphoreImplementedUsingConditionVariable;

/*
	The first reader - writer problem: Reader Preference
*/

class ReaderWriterProblemII
{
private:
	string m_Content;
	int m_nReaders;
	int m_nWriters;
	Semaphore m_sReadTry;
public:

	ReaderWriterProblemII(int nReaders, int nWriters) : m_nReaders(nReaders), m_nWriters(nWriters),
		m_sReadTry(1)
	{
		vector<thread> readers;
		for (int i = 0; i < nReaders; ++i)
		{
			readers.push_back(thread(ReaderWriterProblemII::Read, this));
		}

		thread writer = thread(ReaderWriterProblemII::Write, this);

		for (auto &t : readers)
		{
			t.join();
		}
		writer.join();
	}

	static void Read(ReaderWriterProblemII *rwp)
	{
		string curr;
		while (rwp->m_Content.length() < 200)
		{


			curr += rwp->m_Content;

			int time = std::rand() % 1;
			this_thread::sleep_for(chrono::microseconds(time));

		}
		cout << endl << this_thread::get_id() << curr << endl;
	}

	static void Write(ReaderWriterProblemII *rwp)
	{
		while (rwp->m_Content.length() < 200)
		{
			int time = std::rand() % 100;
			rwp->m_Content += " I am writing" + to_string(time);

			this_thread::sleep_for(chrono::microseconds(time));

		}
	}
};