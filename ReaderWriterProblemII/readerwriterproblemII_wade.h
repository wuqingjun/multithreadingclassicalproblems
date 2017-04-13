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
	int m_nReaders;
	int m_nWriters;
	string m_Content;
	SemaphoreImplementedUsingConditionVariable::Semaphore m_sReadTry;
	SemaphoreImplementedUsingConditionVariable::Semaphore m_sReadCount;
	SemaphoreImplementedUsingConditionVariable::Semaphore m_sWriteCount;
	SemaphoreImplementedUsingConditionVariable::Semaphore m_sResource;
public:

	ReaderWriterProblemII(int nReaders, int nWriters) : m_sReadTry(1), m_sWriteCount(1),
		m_sReadCount(1), m_sResource(1), m_nReaders(nReaders), m_nWriters(nWriters)
	{
		vector<thread> readers;
		for (int i = 0; i < nReaders; ++i)
		{
			readers.push_back(thread(ReaderWriterProblemII::Read, this));
		}

		vector<thread> writers;
		for (int i = 0; i < nWriters; ++i)
		{
			writers.push_back(thread(ReaderWriterProblemII::Write, this));
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

	static void Read(ReaderWriterProblemII *rwp)
	{
		while (rwp->m_Content.length() < 200)
		{
			rwp->m_sReadTry.P();
			rwp->m_sReadCount.P();
			if (++rwp->m_nReaders == 1) rwp->m_sResource.P();
			
			rwp->m_sReadCount.V();
			rwp->m_sReadTry.V();

			cout << endl << this_thread::get_id() << " " << rwp->m_Content << endl;

			int time = std::rand() % 100;
			this_thread::sleep_for(chrono::microseconds(time));

			rwp->m_sReadCount.P();
			if (--rwp->m_nReaders == 0) rwp->m_sResource.V();
			rwp->m_sReadCount.V();
		}
	}

	static void Write(ReaderWriterProblemII *rwp)
	{
		while (rwp->m_Content.length() < 200)
		{
			rwp->m_sWriteCount.P();
			if (++rwp->m_nWriters == 1) rwp->m_sReadTry.P();
			rwp->m_sWriteCount.V();
			
			rwp->m_sResource.P();

			int time = std::rand() % 100;

			rwp->m_Content += " I am writing" + to_string(time);

			this_thread::sleep_for(chrono::microseconds(time));

			rwp->m_sResource.V();

			rwp->m_sWriteCount.P();
			if (--rwp->m_nWriters == 0) rwp->m_sReadTry.V();
			rwp->m_sWriteCount.V();
		}
	}
};