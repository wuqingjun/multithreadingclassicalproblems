#pragma once
#include "stdafx.h"
#include <condition_variable>
#include <queue>
using namespace std;


class BlockQueue
{
private:
	queue<int> queue_data;
	mutable mutex mtxQueue;
	condition_variable cvQueue;
public:
	void push(int val) {
		lock_guard<mutex> lk(mtxQueue);
		queue_data.push(val);
		cvQueue.notify_one();
	}

	void wait_and_pop(int &val) {
		unique_lock<mutex> lk(mtxQueue);
		cvQueue.wait(lk, [this] {return !queue_data.empty(); });
		val = queue_data.front();
		queue_data.pop();
	} 

	bool empty() const {
		lock_guard<mutex> lk(mtxQueue);
		return queue_data.empty();
	}
};