#include "hash.h"
#include <functional>
#include <iostream>

Hash::Hash():mLast(nullptr) 
{
	for (int i = 0; i < ARRAY_SIZE; i++)
		mArr[i] = nullptr;
}
Hash::~Hash()
{
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		if (mArr[i] != nullptr)
			delete mArr[i];
	}
}
void Hash::insert(const std::string& s, int offset)
{
	Node p(offset, s, nullptr); // make the node
	int arrVal = hashVal(s);
	if (mArr[arrVal] == nullptr)
		mArr[arrVal] = new std::list<Node>;
	mArr[arrVal]->push_back(p); // add node to correct place in table
	if (mLast != nullptr) // if this isn't the first Node
	{
		mLast->next = &(mArr[arrVal]->back()); // make the previous node's next this one
	}
	mLast = &(mArr[arrVal]->back()); // update last node
}

bool Hash::find(const std::string& s, int &offset, Node* &p)
{
	int arrVal = hashVal(s);
	if (mArr[arrVal] == nullptr)
		return false;
	for (std::list<Node>::iterator it = mArr[arrVal]->begin(); it != mArr[arrVal]->end(); it++)
	{
		if (it->data == s && !it->used)
		{
			offset = it->offset;
			p = &(*it);
			return true;
		}
	}
	return false;
}

int Hash::hashVal(const std::string& s)
{
	std::hash<std::string> str_hash;
	unsigned int hashValue = str_hash(s);
	return hashValue % ARRAY_SIZE;
}