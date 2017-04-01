// WindowsCppTester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\..\SemaphoreImplementedUsingAtomic\sempaphoreimplementedusingatomic_test.h"
#include "..\..\EfficientLogging\efficientloggingclass_test.h"


void TestSemaphoreUsingAtomic()
{
	SemaphoreTest test;

	test.Test();
}

void TestEfficientLogging()
{
	LogTest test;
	test.Test();
}

int main()
{
	TestEfficientLogging();

    return 0;
}

