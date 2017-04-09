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

template<size_t childrenNumber, class T>
struct Node
{
	T * person;
	vector<atomic<Node *> > children;
	Node() : children(childrenNumber), person(NULL){
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

template<class T, class Indexer = StringIndexer>
class Trie
{
private:
	Node<Indexer::ChildrenSize, T> *m_root;
public:
	Trie() : m_root(new Node<Indexer::ChildrenSize, T>()) {}
	void Add(string key, T *person)
	{
		auto idx = Indexer();
		Node<Indexer::ChildrenSize, T> * curr = m_root;
		for (auto n : key)
		{
			int i = idx(n);
			Node<Indexer::ChildrenSize, T> *newNode = new Node<Indexer::ChildrenSize, T>();
			for (Node<Indexer::ChildrenSize, T> * tmp = curr->children[i].load();
				tmp == NULL && !curr->children[i].compare_exchange_weak(tmp, newNode);
				tmp = curr->children[i].load()) {
			}
			if (newNode != curr->children[i]) delete newNode;
			curr = curr->children[i];
			curr->person = person;
		}
	}

	
	T *Search(string name)
	{
		auto idx = Indexer();
		Node<Indexer::ChildrenSize, T> *curr = m_root;
		for (auto n : name)
		{
			curr = curr->children[idx(n)];
		}
		return curr->person;
	}
};