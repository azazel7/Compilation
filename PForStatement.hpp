#pragma once

#include "Node.hpp"

class PForStatement: public Node
{
    std::string i1, i2, i3;
	Node& expressionInit;
	Node& expressionCondition;
	Node& statement;
	public:
		PForStatement(char* i1, Node& expressionInit, char* i2, Node& expressionCondition, char* i3, Node& statement);
		void semanticsCheck(void) const;
		void generateCode(FILE * fd) const;
};
