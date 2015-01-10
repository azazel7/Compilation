#pragma once
#include "Node.hpp"

class Expression: public Node
{
	std::string id;
	Node* expressionOffset;
	Node& expression;
	public:
		Expression(std::string iden, Node& expr, Node* offset = nullptr);
		void semanticsCheck(void) const;
		Type const* getType();
		void generateCode(FILE * fd) const;
		void generateFloatingCode(FILE * fd, bool convert = false) const;
		~Expression();
};
