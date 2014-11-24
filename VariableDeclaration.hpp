#ifndef VARIABLE_DECLARATION_HPP 
#define VARIABLE_DECLARATION_HPP 
#include "Node.hpp"

class VariableDeclaration : public Node 
{
	std::string type;
	std::list<std::string> id;
	public:
	VariableDeclaration(Node* type, Node* identifier);
	void print(void);
};
#endif
