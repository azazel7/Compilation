#pragma once
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
	void generateCode(FILE * fd) const;//This function should be called only by ProgramNode to create global variable
	~VariableDeclaration();
};
