#pragma once

#include "ReadFrequentPhoneBook.h"

class PhoneBookTest
{
public:
	void Test0()
	{
		NameTrie trie;

		vector<string> people({ "john", "wade" });
		for (auto &p : people)
		{
			trie.Add(p);
		}

		auto p = trie.Search("john");
		p = trie.Search("wade");
	}
};