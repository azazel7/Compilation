#include "Node.hpp"
Node::Node()
{
}

Node::Node(std::string name, int id)
{
	this->name = name;
	this->id = id;
}
Node::Node(int id)
{
	this->id = id;
}

Node::~Node()
{
  	for(Node * n:children)
		delete n;
}

void Node::flattenFunction(void)
{
	std::list<Node*> tmpChildren;
	for(Node* node : children) 
	{
		node->getNodeById(tmpChildren, ID_FUNCTION);
		node->getNodeById(tmpChildren, ID_GLOBAL_DECLARATOR);
	}
	children.insert(children.begin(), tmpChildren.begin(), tmpChildren.end());
	deleteAllChildFromId(ID_EXTERNAL_DECLARATION);
}
void Node::flattenStatement(void)
{
	for(Node* n : children)
		n->flattenStatement();
}

void Node::getNodeById(std::list<Node*> &listToFill, int id)
{
	auto it = children.begin();
	while(it != children.end())
	{
		if((*it)->id == id)
		{
			listToFill.push_front(*it);
			children.erase(it++);
		}
		else
		{
			(*it)->getNodeById(listToFill, id);
			it++;
		}
	}
}

void Node::deleteAllChildFromId(int id)
{
	auto it = children.begin();
	while(it != children.end())
	{
		if((*it)->id == id)
		{
			delete (*it);
			children.erase(it++);
		}
		else
		{
			(*it)->deleteAllChildFromId(id);
			it++;
		}
	}
}
void Node::addChild(Node & node)
{
	children.push_front(&node);
}
void Node::print(void)
{
	std::cout << this->name ;
	for(auto it = children.begin(); it != children.end(); it++)
		if(*it != nullptr)
		{
			(*it)->print();
		}
}

void Node::printTree(int deepth, int maxDeepth)
{
	if(maxDeepth >= 0 && deepth > maxDeepth)
		return;
	std::string padding;
	for(int i = 0; i < deepth;i++)
		padding += "_";	

	for(auto it = children.begin(); it != children.end(); it++)
		if(*it != nullptr)
		{
			if((*it)->id == ID_DECLARATION)
			{
				std::cout << padding << (*it)->id << " ";
				std::cout << (*it)->name << std::endl;
			}
			else
			std::cout << padding << (*it)->id << std::endl;
			(*it)->printTree(deepth+1, maxDeepth);
		}
}

void Node::flattenParameter(void)
{
	for(Node* n : children)
		n->flattenParameter();
}

void Node::setId(int id)
{
	this->id = id;
}
int Node::countChildren(void) const
{
	return children.size();
}
std::string Node::getName(void)
{
	return name;
}
int Node::getId(void) const
{
	return id;
}

void Node::createSymboleTable(void)
{
	for(Node* n : children)
		n->createSymboleTable();
}
void Node::semanticsCheck(void) const
{
	for(Node* n : children)
		n->semanticsCheck();
}
void Node::printSymboleTable(void) const
{
	for(Node* n : children)
		n->printSymboleTable();
}
void Node::getSymbole(std::map<std::string, Type*> & symbole) const
{

}
Type* Node::getType(void)
{
	return nullptr;
}
