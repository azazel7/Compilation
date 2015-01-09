#pragma once
#include "Node.hpp"
#include <list>

class PrimaryExpressionFunctionCall : public Node
{
	std::list<Node*> argumentList;
	std::string id;
	public:
		PrimaryExpressionFunctionCall(std::string id, std::list<Node*> argumentList);
		void semanticsCheck(void) const;
		Type const* getType();
		~PrimaryExpressionFunctionCall();
		void generateCode(FILE * fd) const;
		void generateFloatingCode(FILE * fd, bool convert = false) const;
};
