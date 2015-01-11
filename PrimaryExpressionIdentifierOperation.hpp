#pragma once
#include "Node.hpp"

class PrimaryExpressionIdentifierOperation : public Node
{
	std::string name;
	char type;
	public:
		PrimaryExpressionIdentifierOperation(std::string na, char type);
		void semanticsCheck(void);
		Type const* getType();
		void generateCode(FILE * fd) const;
		void generateFloatingCode(FILE * fd, bool convert = false) const;
		static const char dec;
		static const char inc;
};
