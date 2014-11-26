#include "Function.hpp"
#include "Instruction.hpp"

Function::Function(Node* type, Node* argument, Node* body) : Node(ID_FUNCTION), typeNode(*type), bodyNode(*body)
{
	argument->getNodeById(allParameter, ID_PARAMETER);
	nameFunction = argument->getName();
}

void Function::print(void)
{
	std::cout << typeNode.getName() << " " << nameFunction << " (";
	for(Node* n : allParameter)
		n->print();
	std::cout << ")" << std::endl;
	bodyNode.print();

}
void Function::printAsm(int fd)
{
}

void Function::getSymbole(std::map<std::string, Type*> & symbole) const
{
}
void Function::createSymboleTable(void)
{
	for(Node* n : allParameter)
		n->getSymbole(symboleTable);
	bodyNode.createSymboleTable();
}
