#pragma once
#include "efficientloggingclass_wade.h"
#include "efficientlogging_lockfree_wade.h"

class LogTest
{
public:
	void Test0()
	{
		Log log1(100);

		for (int i = 0; i < 10; ++i)
		{
			auto res = log1.WriteLog(string("sometestlogginginformationwrittenintodisk") + to_string(i));
			cout << "WritLog() result" << res << endl;
		}
		
	}

	void Test1()
	{
		LogLockFree log1(100);

		for (int i = 0; i < 10; ++i)
		{
			auto res = log1.WriteLog(string("sometestlogginginformationwrittenintodisk") + to_string(i));
			cout << "WritLog() result" << res << endl;
		}

	}
};