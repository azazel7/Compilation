#ifndef FUNCTION_HPP 
#define FUNCTION_HPP 
#include <list>
#include <map>
#include "Node.hpp"

class Type;

class Function : public Node
{
	std::list<Node*> allParameter;
	std::string nameFunction;
	Node& typeNode; //TODO not sure about it now -> return int* for exemple
	Node& bodyNode; 

	//Contain all offset of the variable in the stack frame
	std::map<std::string, Type const*> symboleTable;
	std::map<std::string, int> offsetTable;
	
	public:
		Function(Node* type, Node* argumentNode, Node* bodyNode);
		void print(void);
		void getSymbole(std::map<std::string, Type const*> & symbole) const;
		void createSymboleTable(void);
		void printSymboleTable(void) const;
		void semanticsCheck(void) const;
		void generateCode(FILE * fd) const;
};
#endif
