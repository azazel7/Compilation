#pragma once
#include "Node.hpp"

class ReturnStatement : public Node
{
	Node* expression;
	public:
		ReturnStatement(Node* l = nullptr);
		void semanticsCheck(void);
		void generateCode(FILE * fd) const;
		~ReturnStatement();
//TODO how to check if the return type of the function is the same as the expression type ?
};
