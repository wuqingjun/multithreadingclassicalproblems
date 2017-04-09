#pragma once

#include "ReadFrequentPhoneBook.h"

class PhoneBookTest
{
public:
	void Test0()
	{
		Trie<StringIndexer> trie;

		vector<Person> people({ Person("john smith", "1111111"), Person("wade wu", "2222222") });
		for (auto &p : people)
		{
			trie.Add(p.Name, &p);
		}

		auto p = trie.Search("john smith");
		p = trie.Search("wade wu");
	}

	void Test1()
	{
		Trie <NumberIndexer> trie;

		vector<Person> people({ Person("john smith", "1111111"), Person("wade wu", "2222222") });
		for (auto &p : people)
		{
			trie.Add(p.PhoneNumber, &p);
		}

		auto p = trie.Search("1111111");
		p = trie.Search("2222222");
	}

	void Test2()
	{
		Trie <AlphaNumericIndexer> trie;

		vector<Person> people({ Person("john smith", "1111111"), Person("wade wu", "2222222") });
		for (auto &p : people)
		{
			trie.Add(p.PhoneNumber, &p);
		}

		for (auto &n : people)
		{
			trie.Add(n.Name, &n);
		}

		auto p = trie.Search("1111111");
		p = trie.Search("2222222");

		auto n = trie.Search("john smith");
		n = trie.Search("wade wu");
	}
};