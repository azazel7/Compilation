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
void CompoundStatement::flattenStatement(void)
{
	//Get all statement among his children
	std::list<Node*> tmpStatement;
	getNodeById(tmpStatement, ID_STATEMENT);	
	children.insert(children.begin(), tmpStatement.begin(), tmpStatement.end());	
	for(Node* n : children)
		n->flattenStatement();
	deleteAllChildFromId(ID_STATEMENT_LIST);
}
