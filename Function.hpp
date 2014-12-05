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
	std::map<std::string, int> allVariableOffset;
	std::map<std::string, Type*> symboleTable;
	public:
		Function(Node* type, Node* argumentNode, Node* bodyNode);
		void printAsm(int fd);	
		void print(void);
		void getSymbole(std::map<std::string, Type*> & symbole) const;
		void createSymboleTable(void);
		void printSymboleTable(void) const;
};
#endif
