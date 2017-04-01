#pragma once

#include "sempaphoreimplementedusingatomic.h"
#include <thread>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <chrono>
using namespace std;


void Producer(Semaphore &sem)
{
	for (int i = 0; i < 10000; ++i)
	{
		int time = std::rand() % 100;
		sem.V();
		this_thread::sleep_for(chrono::microseconds(time));
	}
}

void Consumer(Semaphore &sem)
{
	for (int i = 0; i < 10000; ++i)
	{
		int time = std::rand() % 100;
		sem.P();
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
		thread p(Producer, std::ref(semaphore));
		thread c(Consumer, std::ref(semaphore));

		p.join();
		c.join();
		thread t1(f);
	}


};