#pragma once

#include "PararrelQuickSort.h"
#include <iostream>
using namespace std;

class PararrelQuickSortTest {
public:
	PararrelQuickSortTest() {
		Test1();
	}
public:
	void Test0() {
		list<int> l{ 4, 1, 3, 6, 5, 2 };
		auto res = pararrel_quick_sort(l);
		for (auto n : res) {
			cout << n << endl;
		}
	}

	void Test1() {
		vector<int> nums{4, 1, 3, 6, 5, 2};
		quickSort(begin(nums), end(nums));
		for (auto n : nums) {
			cout << n << endl;
		}
	}
};