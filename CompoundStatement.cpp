#include "CompoundStatement.hpp"
#include <iostream>
#include <list>
#include <algorithm>
#include "StackSymboleTable.hpp"

CompoundStatement::CompoundStatement():Node()
{
}
CompoundStatement::CompoundStatement(int id):Node(id)
{
}
CompoundStatement::CompoundStatement(std::string name, int id): Node(name, id)
{
}
CompoundStatement::CompoundStatement(Node* statement, Node* declaration) : Node(ID_COUMPOUND_STATEMENT)
{
	if(declaration != nullptr)
	{
		declaration->getNodeById(allDeclaration, ID_DECLARATION);
		if(allDeclaration.size() == 0)
			allDeclaration.push_front(declaration);
		else
			delete declaration;
	}
	statement->getNodeById(allStatement, ID_STATEMENT);
	if(allStatement.size() == 0)
		allStatement.push_front(statement);
	else
		delete statement;
	std::reverse(allStatement.begin(), allStatement.end());
}
void CompoundStatement::semanticsCheck(void) const
{
	for(Node* statement : allStatement)
		statement->semanticsCheck();
}

void CompoundStatement::print(void)
{
	std::cout << std::endl << "{" << std::endl;
	for(Node* n : allDeclaration)
	{
		n->print();
		std::cout << std::endl;
	}
	std::cout << std::endl;

	for(Node* n : allStatement)
	{
		n->print();
		n->printTree(0);
	}
	std::cout << "}" << std::endl;
}
void CompoundStatement::getSymbole(std::map<std::string, Type const*> & symbole) const
{
	for(Node* n : allDeclaration)
		n->getSymbole(symbole);
	for(Node* n : allStatement)
		n->getSymbole(symbole);
}
CompoundStatement::~CompoundStatement()
{
	for(Node* node : allStatement)
		delete node;
	for(Node* node : allDeclaration)
		delete node;
}
void CompoundStatement::generateCode(FILE * fd) const
{
	for(Node const* statement : allStatement)
		statement->generateCode(fd);
}
