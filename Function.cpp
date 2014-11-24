#include "Function.hpp"
#include "Instruction.hpp"

Function::Function(Node* type, Node* argument, Node* body) : Node(ID_FUNCTION), typeNode(*type), bodyNode(*body)
{
	argument->getNodeById(allParameter, ID_PARAMETER);
	nameFunction = argument->getName();
}

void Function::print(void)
{
	std::cout << typeNode.getName() << " " << nameFunction << " " << std::endl << "Arg:";
	for(Node* n : allParameter)
		n->print();
	std::cout << std::endl;
	bodyNode.print();

}
void Function::printAsm(int fd)
{
	for(Instruction* i : allInstruction)
		i->printAsm(fd);
}
