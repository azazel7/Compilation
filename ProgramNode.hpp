#pragma once

#include <map>
#include <string>
#include "Node.hpp"

class ProgramNode : public Node
{
	std::map<std::string, Type const*> symboleTable;
	public:
		ProgramNode();
		void createSymboleTable(void);
		void semanticsCheck(void) const;
		void generateCode(FILE * fd) const;
		~ProgramNode();

};
