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

class ReaderWriterProblemIII
{
private:
	int m_nReadCount;
	string m_Content;
	SemaphoreImplementedUsingConditionVariable::Semaphore m_sResourceAccess;
	SemaphoreImplementedUsingConditionVariable::Semaphore m_sReadCountAccess;
	SemaphoreImplementedUsingConditionVariable::Semaphore m_sServiceQueueAccess;
public:

	ReaderWriterProblemIII(int nReaders, int nWriters): m_nReadCount(0), m_sResourceAccess(1), m_sReadCountAccess(1), m_sServiceQueueAccess(1)
	{
		vector<thread> readers;
		for (int i = 0; i < nReaders; ++i)
		{
			readers.push_back(thread(ReaderWriterProblemIII::Read, this));
		}

		vector<thread> writers;
		for (int i = 0; i < nWriters; ++i)
		{
			writers.push_back(thread(ReaderWriterProblemIII::Write, this));
		}

		for (auto &t : readers)
		{
			t.join();
		}

		for (auto &t : writers)
		{
			t.join();
		}
	}

	static void Read(ReaderWriterProblemIII *rwp)
	{
		while (rwp->m_Content.length() < 200)
		{
			rwp->m_sServiceQueueAccess.P();
			rwp->m_sReadCountAccess.P();
			if (++rwp->m_nReadCount == 1) rwp->m_sResourceAccess.P();

			rwp->m_sServiceQueueAccess.V();
			rwp->m_sReadCountAccess.V();
			
			cout << endl << this_thread::get_id() << " " << rwp->m_Content << endl;

			int time = std::rand() % 100;
			this_thread::sleep_for(chrono::microseconds(time));

			rwp->m_sReadCountAccess.P();
			if (--rwp->m_nReadCount == 0) rwp->m_sResourceAccess.V();
			rwp->m_sReadCountAccess.V();
		}
	}

	static void Write(ReaderWriterProblemIII *rwp)
	{
		while (rwp->m_Content.length() < 200)
		{
			rwp->m_sServiceQueueAccess.P();
			rwp->m_sResourceAccess.P();
			rwp->m_sServiceQueueAccess.V();

			int time = std::rand() % 100;

			rwp->m_Content += " I am writing" + to_string(time);

			this_thread::sleep_for(chrono::microseconds(time));

			rwp->m_sResourceAccess.V();
		}
	}
};