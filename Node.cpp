#include "Node.hpp"
Node::Node()
{
}

Node::Node(std::string name)
{
	this->name = name;
}

Node::~Node()
{
  	for(Node * n:children)
		delete n;
}


void Node::addChild(Node & node)
{
	children.push_front(&node);
}
void Node::print(void)
{
	std::cout << this->name;
	for(auto it = children.begin(); it != children.end(); it++)
		if(*it != nullptr)
			(*it)->print();
}
