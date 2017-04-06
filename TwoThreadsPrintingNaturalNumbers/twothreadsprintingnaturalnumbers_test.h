#pragma once

#include "twothreadsprintingnaturalnumbers_wade_conditionvariable.h"

class TwoThreadsPrintingTest
{
public:
	void Test()
	{
		TwoThreasPrintingNaturalNumbers twoThreads(100);
		twoThreads.createThreads();
	}
};