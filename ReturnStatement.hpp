#ifndef RETURN_STATEMENT_HPP
#define RETURN_STATEMENT_HPP
#include "Node.hpp"

class ReturnStatement : public Node
{
	Node* expression;
	public:
		ReturnStatement(Node* l = nullptr);
		void semanticsCheck(void) const;
//TODO how to check if the return type of the function is the same as the expression type ?
};
#endif
