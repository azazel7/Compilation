#pragma once
#include "Node.hpp"

class AdditiveExpression : public Node
{
	char type;
	Node& right;
	Node& left;
	public:
		AdditiveExpression(Node& r, Node& l, char t);
		void semanticsCheck(void) const;
		Type const* getType();
		void generateCode(FILE * fd) const;
		void generateFloatingCode(FILE * fd, bool convert = false) const;
	static const char sub;
	static const char add;
};
