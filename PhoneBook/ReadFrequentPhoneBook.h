#pragma once

#include <string>
#include <vector>
#include <atomic>
using namespace std;

struct Person
{
public: 
	Person(string n, string p) : Name(n), PhoneNumber(p) {}
	string Name;
	string PhoneNumber;
};

struct Node
{
	Person * person;
	vector<atomic<Node *> > children;
	Node() : children(26){
		for (int i = 0; i < 26; ++i) {
			children[i] = NULL;
		}
	}
};

class NameTrie
{
private:
	Node *m_root;
public:
	NameTrie() : m_root(new Node() ){}
	void Add(string name)
	{
		Node * curr = m_root;
		for (auto n : name)
		{
			int i = n - 'a';
			Node *newNode = new Node();
			for (Node * tmp = curr->children[i].load(); 
				tmp == NULL && !curr->children[i].compare_exchange_weak(tmp, newNode); 
				tmp = curr->children[i].load()) {}
			if (newNode != curr->children[i]) delete newNode;
			curr = curr->children[i];
			curr->person = new Person("testname", "33112");
		}
	}

	Person *Search(string name)
	{
		Node *curr = m_root;
		for (auto n : name)
		{
			curr = curr->children[n - 'a'];
		}
		return curr->person;
	}
};