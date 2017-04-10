#pragma once

#include "twothreadsprintingnaturalnumbers_wade_conditionvariable.h"
#include "twothreadsprintingnaturalnumbers_lockfree_wade.h"
#include "twothreadsprintingnaturalnumbers_wade_twoconditionvariables.h"

class TwoThreadsPrintingTest
{
public:
	void Test()
	{
		TwoThreasPrintingNaturalNumbers twoThreads(100);
		twoThreads.createThreads();
	}

	void Test1()
	{
		TwoThreasPrintingNaturalNumbersLockFree twoThreads(100);
		twoThreads.createThreads();
	}

	void Test2()
	{
		TwoThreasPrintingNaturalNumbersTwoVariables twoThreads(100);
		twoThreads.createThreads();
	}
};