#pragma once

#include "semaphoreimplementedusingconditionvariable_wade.h"
#include <thread>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <chrono>
#include <cassert>
using namespace std;
using namespace SemaphoreImplementedUsingConditionVariable;



class SemaphoreImplementedUsingConditionVariableTest
{
private:
	SemaphoreImplementedUsingConditionVariable::Semaphore semaphore;
public:
	static void Producer(SemaphoreImplementedUsingConditionVariable::Semaphore &sem)
	{
		for (int i = 0; i < 1000; ++i)
		{
			int time = std::rand() % 100;
			sem.V();
			cout << "before V(): " << sem.getCount() << endl;
			assert(sem.getCount() <= 10 && sem.getCount() >= 0);
			cout << "after V(): " << sem.getCount() << endl;
			this_thread::sleep_for(chrono::microseconds(time));
		}
	}

	static void Consumer(SemaphoreImplementedUsingConditionVariable::Semaphore &sem)
	{
		for (int i = 0; i < 1000; ++i)
		{
			int time = std::rand() % 100;
			sem.P();
			cout << "before P(): " << sem.getCount() << endl;
			assert(sem.getCount() <= 10 && sem.getCount() >= 0);
			this_thread::sleep_for(chrono::microseconds(time));
		}
	}

public:
	SemaphoreImplementedUsingConditionVariableTest() : semaphore(10) {}
	void Test()
	{
		for (int i = 0; i < 2; ++i)
		{
			srand(0);
			thread p(Producer, std::ref(semaphore));
			thread c(Consumer, std::ref(semaphore));

			p.join();
			c.join();
		}
	}
};