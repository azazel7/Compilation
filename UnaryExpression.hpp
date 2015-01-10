#pragma once
#include "Node.hpp"

class UnaryExpression: public Node
{
	Type* typeUnarayExpression;
	Node& expression;
	char type;
	Type const* getType() const; 
	public:
		UnaryExpression(Node& l);
		void semanticsCheck(void) const;
		Type const* getType(); 
		void generateCode(FILE * fd) const;
		void generateFloatingCode(FILE * fd, bool convert = false) const;
		~UnaryExpression();
	static const char neg;
	static const char no;
};
