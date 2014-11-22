#include "Function.hpp"
#include "Instruction.hpp"

Function::Function(Node& type, Node& argument, Node& body) : Node(ID_FUNCTION), typeNode(type), argumentNode(argument), bodyNode(body)
{}

void Function::printAsm(int fd)
{
	for(Instruction* i : allInstruction)
		i->printAsm(fd);
}
