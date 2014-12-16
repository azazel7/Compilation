#ifndef VARIABLE_DECLARATION_HPP 
#define VARIABLE_DECLARATION_HPP 
#include "Node.hpp"

class Type;
class IdentifierDeclarator;

class VariableDeclaration : public Node 
{
	std::string type;
	std::list<IdentifierDeclarator*> id;
	public:
	static bool isPointedId(std::string const& id);
	VariableDeclaration(Node* type, Node* identifier);
	void print(void);
	Type* getType(void);
	void getSymbole(std::map<std::string, Type const*> & symbole) const;
};
#endif
