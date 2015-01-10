#pragma once
#include "Node.hpp"

class MultiplicativeExpression : public Node
{
	Node& right;
	Node& left;
	public:
		MultiplicativeExpression(Node& r, Node& l);
		void semanticsCheck(void) const;
		Type const* getType();
		void generateCode(FILE * fd) const;
		void generateFloatingCode(FILE * fd, bool convert) const;
		~MultiplicativeExpression();
};
