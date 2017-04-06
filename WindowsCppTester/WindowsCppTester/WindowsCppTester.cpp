// WindowsCppTester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\..\SemaphoreImplementedUsingAtomic\sempaphoreimplementedusingatomic_test.h"
#include "..\..\EfficientLogging\efficientloggingclass_test.h"
#include "..\..\TwoThreadsPrintingNaturalNumbers\twothreadsprintingnaturalnumbers_test.h"


void TestSemaphoreUsingAtomic()
{
	SemaphoreTest test;

	test.Test();
}

void TestEfficientLogging()
{
	LogTest test;
	test.Test1();
}

void TestTwoThreads()
{
	TwoThreadsPrintingTest test;
	test.Test1();
}

int main()
{
	//TestEfficientLogging();
	TestTwoThreads();

    return 0;
}

