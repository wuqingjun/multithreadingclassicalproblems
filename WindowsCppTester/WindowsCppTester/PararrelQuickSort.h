#pragma once

#include <list>
#include <algorithm>
#include <future>
#include <mutex>
using namespace std;

list<int> pararrel_quick_sort(list<int> input) {
	if (input.empty()) return input;

	list<int> result;
	result.splice(begin(result), input, input.begin());
	int pivot = *result.begin();

	auto divPos = partition(begin(input), end(input), [&](int & e) {return e < pivot; });
	list<int> lower_part;
	lower_part.splice(end(lower_part), input, begin(input), divPos);
	auto new_lower(async(pararrel_quick_sort, move(lower_part)));
	auto higher(pararrel_quick_sort(move(input)));
	result.splice(begin(result), new_lower.get());
	result.splice(end(result), higher);
	return result;
}


void quickSort(vector<int>::iterator l, vector<int>::iterator h) {
	if (l != h) {
		int pivot = *l;
		auto divPos = partition(l, h, [&](const int e) {return e < *l; });
		auto lower = async(quickSort, l, divPos);
		quickSort(divPos + 1, h);
		lower.get();
	}
}

void testMutex() {
	mutex m;
	
}