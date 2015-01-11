#pragma once
#include "Node.hpp"

class ExpressionStatement: public Node
{
	Node& expression;
	public:
		ExpressionStatement(Node& expression);
		void semanticsCheck(void);
		void generateCode(FILE * fd) const;
		~ExpressionStatement();
};

