#include "CompoundStatement.hpp"
#include <iostream>
#include <list>
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
		declaration->print();
		declaration->getNodeById(allDeclaration, ID_DECLARATION);
		if(allDeclaration.size() == 0)
			allDeclaration.push_front(declaration);
	}
	statement->getNodeById(allStatement, ID_STATEMENT);
	if(allStatement.size() == 0)
		allStatement.push_front(statement);
}
void CompoundStatement::flattenStatement(void)
{
}
void CompoundStatement::semanticsCheck(void) const
{
	StackSymboleTable::push(symboleTable);
	for(Node* statement : allStatement)
		statement->semanticsCheck();
	StackSymboleTable::pop();
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
void CompoundStatement::createSymboleTable(void)
{
	for(Node* n : allDeclaration)
		n->getSymbole(symboleTable);
	for(Node* n : allStatement)
		n->createSymboleTable();
}
void CompoundStatement::printSymboleTable(void) const
{
	std::cout <<"{" << std::endl;
	for(auto symbole : symboleTable)
	{
		std::cout << symbole.first << " ";
		symbole.second->print();
		std::cout << std::endl;
	}
	for(Node* statement : allStatement)
		statement->printSymboleTable();
	std::cout <<"}" << std::endl;
}
