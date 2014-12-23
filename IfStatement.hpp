#ifndef IF_STATEMENT_HPP
#define IF_STATEMENT_HPP

#include "Node.hpp"

class IfStatement : public Node
{
	Node& expression;
	Node& statement;
	Node* elseStatement;
	public:
		IfStatement(Node& expression, Node& statement, Node* elseStatement = nullptr );
		void semanticsCheck(void) const;
		void generateCode(FILE * fd) const;
};
#endif
