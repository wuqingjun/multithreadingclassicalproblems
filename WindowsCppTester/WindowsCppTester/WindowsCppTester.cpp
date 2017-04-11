// WindowsCppTester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\..\SemaphoreImplementedUsingAtomic\sempaphoreimplementedusingatomic_test.h"
#include "..\..\EfficientLogging\efficientloggingclass_test.h"
#include "..\..\TwoThreadsPrintingNaturalNumbers\twothreadsprintingnaturalnumbers_test.h"
#include "..\..\PhoneBook\ReadFrequentPhoneBook_test.h"
#include "..\..\ReaderWriterProblemI\readerwriterproboemI_test.h"

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
	test.Test2();
}

void TestPhoneBook()
{
	PhoneBookTest test;
	test.Test0();
	test.Test1();
	test.Test2();
}

void TestReaderWriter()
{
	ReaderWriterProblemITest test;
	test.Test1();
}

int main()
{
	//TestEfficientLogging();
	//TestTwoThreads();
	//TestPhoneBook();b
	TestReaderWriter();
    return 0;
}

