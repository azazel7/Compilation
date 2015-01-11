#pragma once
#include "Node.hpp"

class PrimaryExpressionArrayAccess: public Node
{
	std::string id;
	Node& expression;
	public:
		PrimaryExpressionArrayAccess(std::string id, Node& expression);
		void semanticsCheck(void);
		Type const* getType();
		void generateCode(FILE * fd) const;
		void generateFloatingCode(FILE * fd, bool convert) const;
		~PrimaryExpressionArrayAccess();
};
