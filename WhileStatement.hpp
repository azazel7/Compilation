#ifndef WHILE_STATEMENT_HPP
#define WHILE_STATEMENT_HPP

#include "Node.hpp"

class WhileStatement: public Node
{
	Node& expression;
	Node& statement;
	public:
		WhileStatement(Node& expression, Node& statement);
		void semanticsCheck(void) const;
		void generateCode(FILE * fd) const;
};
#endif

