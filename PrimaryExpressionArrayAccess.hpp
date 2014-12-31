#pragma once
#include "Node.hpp"

class PrimaryExpressionArrayAccess: public Node
{
	std::string id;
	Node& expression;
	public:
		PrimaryExpressionArrayAccess(std::string id, Node& expression);
		void semanticsCheck(void) const;
		Type const* getType();
		void generateCode(FILE * fd) const;
		~PrimaryExpressionArrayAccess();
};
