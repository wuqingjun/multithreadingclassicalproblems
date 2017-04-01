#pragma once

#include "sempaphoreimplementedusingatomic.h"
#include <thread>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <chrono>
#include <cassert>
using namespace std;



void Producer(Semaphore &sem)
{
	for (int i = 0; i < 10000; ++i)
	{
		
		int time = std::rand() % 100;
		sem.V();
		assert(sem.getCount() <= 10);
		cout << "after V(): " << sem.getCount() << endl;
		this_thread::sleep_for(chrono::microseconds(time));
	}
}

void Consumer(Semaphore &sem)
{
	for (int i = 0; i < 10000; ++i)
	{
		int time = std::rand() % 100;
		sem.P();
		assert(sem.getCount() <= 10);
		cout << "after P(): " << sem.getCount() << endl;
		this_thread::sleep_for(chrono::microseconds(time));
	}
}

void f()
{

}


class SemaphoreTest
{
private: 
	Semaphore semaphore;
public:
	SemaphoreTest() : semaphore(10){}
	void Test()
	{
		for (int i = 0; i < 5; ++i)
		{
			srand(0);
			thread p(Producer, std::ref(semaphore));
			thread c(Consumer, std::ref(semaphore));

			p.join();
			c.join();
		}

	}


};