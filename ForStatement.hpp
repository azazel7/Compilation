#pragma once
#include "Node.hpp"

class ForStatement: public Node
{
	Node& expressionVariation;
	Node& expressionInit;
	Node& expressionCondition;
	Node& statement;
	public:
		ForStatement(Node& expressionInit, Node& expressionCondition, Node& expressionVariation, Node& statement);
		void semanticsCheck(void) const;
		void generateCode(FILE * fd) const;
		~ForStatement();
};
