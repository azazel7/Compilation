#include "CompoundStatement.hpp"
#include <list>

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
void CompoundStatement::getSymbole(std::map<std::string, Type*> & symbole) const
{
}
void CompoundStatement::createSymboleTable(void)
{
	for(Node* n : allDeclaration)
		n->getSymbole(symboleTable);
	for(Node* n : allStatement)
		n->createSymboleTable();
}
