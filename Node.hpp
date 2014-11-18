#include <iostream>
#include <list>

class Node
{
	std::list<Node*> children;
	std::string name;
	public:
		Node();
		Node(std::string name);
		~Node();
		void addChild(Node& node);
		void print(void);
};
