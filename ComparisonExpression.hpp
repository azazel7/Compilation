#ifndef COMPARISON_EXPRESSION_HPP
#define COMPARISON_EXPRESSION_HPP
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
		static const char LE;
		static const char L;
		static const char GE;
		static const char G;
		static const char EQ;
		static const char NE;
};
#endif
