#ifndef FOR_STATEMENT_HPP
#define FOR_STATEMENT_HPP

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
};
#endif


