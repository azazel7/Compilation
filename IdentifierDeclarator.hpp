#pragma once
#include "Node.hpp"

class IdentifierDeclarator: public Node
{ 
	bool pointed = false;
	int size = 0;
	public:
		IdentifierDeclarator(std::string name, bool pointed = false);
		IdentifierDeclarator(std::string name, int size);
		bool isPointed(void) const;
		int getSize(void) const;
		
};
