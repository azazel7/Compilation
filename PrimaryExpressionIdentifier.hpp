#pragma once
#include "Node.hpp"

class PrimaryExpressionIdentifier: public Node
{
	std::string name;
	public:
		PrimaryExpressionIdentifier(std::string name);
		void semanticsCheck(void) const;
		Type const* getType();
		void generateCode(FILE * fd) const;
		void generateFloatingCode(FILE * fd, bool convert = false) const;

};
