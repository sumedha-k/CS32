#ifndef NODE_H
#define NODE_H
struct Node
{
	Node(int offset, std::string data, Node* next) :offset(offset), data(data), next(next)
	{}
	int offset;
	std::string data;
	Node* next;
	bool used = false;
};
#endif
