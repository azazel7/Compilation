#include "Node.hpp"
#include "Type.hpp"

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
void Node::semanticsCheck(void)
{
	for(Node* n : children)
		n->semanticsCheck();
}
void Node::printSymboleTable(void) const
{
	for(Node* n : children)
		n->printSymboleTable();
}
void Node::getSymbole(std::map<std::string, Type const*> & symbole) const
{

}
Type const* Node::getType(void)
{
	return nullptr;
}
std::list<Node*> Node::getChildren(void)
{
	std::list<Node*> tmp = children;
	children.clear();
	return tmp;
}
void Node::generateCode(FILE * fd) const
{
	for(Node const* node : children)
		node->generateCode(fd);
}
void Node::generateFloatingCode(FILE * fd, bool convert) const
{
	for(Node const* node : children)
		node->generateFloatingCode(fd, convert);
}
void Node::generateSubCode(FILE * fd, Node& right, Node& left)
{
	//Only call by generateCode, never by generateFloatingCode
	if(right.getType()->getType() == FLOAT_TYPE)
		right.generateFloatingCode(fd, true);	
	else
		right.generateCode(fd);
	if(left.getType()->getType() == FLOAT_TYPE)
		left.generateFloatingCode(fd, true);	
	else
		left.generateCode(fd);
}
std::string Node::convertToInteger(void)
{
	return "cvttss2si (%%esp), %%eax\npop %%ebx\npush %%eax\n";
}
std::string Node::convertToFloat(void)
{
	return "cvtsi2ssl (%%esp), %xmm1\nmovss %%xmm1, %%eax\npop %%ebx\npush %%eax\n";
}
