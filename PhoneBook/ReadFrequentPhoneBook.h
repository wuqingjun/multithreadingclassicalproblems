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

template<size_t childrenNumber>
struct Node
{
	Person * person;
	vector<atomic<Node *> > children;
	Node() : children(childrenNumber){
		for (int i = 0; i < childrenNumber; ++i) {
			children[i] = NULL;
		}
	}
};

struct StringIndexer
{
	static const size_t ChildrenSize = 27;
	int operator()(char c)
	{
		return c == ' ' ? ChildrenSize - 1 : c - 'a';
	}
};

struct NumberIndexer
{
	static const size_t ChildrenSize = 10;
	int operator()(char n)
	{
		return n - '0';
	}
};

struct AlphaNumericIndexer
{
	static const size_t ChildrenSize = 37;
	int operator()(char c)
	{
		if (c >= '0' && c <= '9')  return c - '0';
		else if (c == ' ') return 36;
		return c - 'a' + 10;
	}
};

template<class Indexer = StringIndexer>
class Trie
{
private:
	Node<Indexer::ChildrenSize> *m_root;
public:
	Trie() : m_root(new Node<Indexer::ChildrenSize>()) {}
	void Add(string key, Person *person)
	{
		auto idx = Indexer();
		Node<Indexer::ChildrenSize> * curr = m_root;
		for (auto n : key)
		{
			int i = idx(n);
			Node<Indexer::ChildrenSize> *newNode = new Node<Indexer::ChildrenSize>();
			for (Node<Indexer::ChildrenSize> * tmp = curr->children[i].load();
				tmp == NULL && !curr->children[i].compare_exchange_weak(tmp, newNode);
				tmp = curr->children[i].load()) {
			}
			if (newNode != curr->children[i]) delete newNode;
			curr = curr->children[i];
			curr->person = person;
		}
	}

	
	Person *Search(string name)
	{
		auto idx = Indexer();
		Node<Indexer::ChildrenSize> *curr = m_root;
		for (auto n : name)
		{
			curr = curr->children[idx(n)];
		}
		return curr->person;
	}
};