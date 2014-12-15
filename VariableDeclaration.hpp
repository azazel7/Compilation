#ifndef VARIABLE_DECLARATION_HPP 
#define VARIABLE_DECLARATION_HPP 
#include "Node.hpp"

class Type;

class VariableDeclaration : public Node 
{
	std::string type;
	std::list<std::string> id;
	bool isPointedId(std::string id) const;
	public:
	VariableDeclaration(Node* type, Node* identifier);
	void print(void);
	Type* getType(void);
	void getSymbole(std::map<std::string, Type const*> & symbole) const;
};
#endif
