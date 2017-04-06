#pragma once

#include <string>
#include <vector>
using namespace std;

struct Person
{
	string Name;
	string PhoneNumber;
};

struct Node
{
	char c;
	Person * person;
	vector<Node *> children;
	Node(char c1) : c(c), children(26, NULL) {}
};

class NameTrie
{
private:
	Node *root;
public:
	NameTrie() : root(NULL) {}
	void Add(string number)
	{
		for (auto n : number)
		{

		}
	}
};