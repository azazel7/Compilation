#ifndef COMPOUND_STATEMENT_HPP 
#define COMPOUND_STATEMENT_HPP
#include "Node.hpp"
#include <list>

class CompoundStatement : public Node
{
	std::list<Node*> allDeclaration;
	std::list<Node*> allStatement;
	
	public:
		CompoundStatement();
		CompoundStatement(int id);
		CompoundStatement(std::string name, int id = -1);
		CompoundStatement(Node* statement, Node* declaration = nullptr);
		void flattenStatement(void);
		void print(void);
};
#endif 

