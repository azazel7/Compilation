#pragma once
#include "Node.hpp"

class IfStatement : public Node
{
	Node& expression;
	Node& statement;
	Node* elseStatement;
	public:
		IfStatement(Node& expression, Node& statement, Node* elseStatement = nullptr );
		void semanticsCheck(void);
		void generateCode(FILE * fd) const;
};
