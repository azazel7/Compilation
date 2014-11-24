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
		declaration->getNodeById(allDeclaration, ID_DECLARATION);
	statement->printTree(0, 14);
	statement->getNodeById(allStatement, ID_STATEMENT);
	std::cout << std::endl << allStatement.size() << std::endl;
	statement->printTree(0, 14);
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
		n->print();
	std::cout << "}" << std::endl;
}
