#ifndef FUNCTION_HPP 
#define FUNCTION_HPP 
#include <list>
#include <map>
#include "Node.hpp"
class Instruction;

class Function : public Node
{
	std::list<Node*> allParameter;
	std::string nameFunction;
	Node& typeNode; //TODO not sure about it now -> return int* for exemple
	Node& bodyNode; 

	std::list<Instruction*> allInstruction;

	//Contain all offset of the variable in the stack frame
	std::map<std::string, int> allVariableOffset;
	public:
		Function(Node* type, Node* argumentNode, Node* bodyNode);
		void printAsm(int fd);	
		void print(void);
};
#endif
