#pragma once
#include "Node.hpp"

class ComparisonExpression : public Node
{
	Type* type;
	Node& right;
	Node& left;
	char typeOp;
	public:
		ComparisonExpression(Node& right, Node &left, char t);
		void semanticsCheck(void) const;
		Type const* getType();
		void generateCode(FILE * fd) const;
		void generateFloatingCode(FILE * fd, bool convert = false) const;
		static const char LE;
		static const char L;
		static const char GE;
		static const char G;
		static const char EQ;
		static const char NE;
		~ComparisonExpression();
};
