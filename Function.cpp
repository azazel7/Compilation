#include "Function.hpp"
#include <stdexcept>
#include "FunctionType.hpp"
#include "PrimitiveType.hpp"

Function::Function(Node* type, Node* argument, Node* body) : Node(ID_FUNCTION), typeNode(*type), bodyNode(*body)
{
	argument->getNodeById(allParameter, ID_PARAMETER);
	nameFunction = argument->getName();
	for(Node* n : allParameter)
		n->getSymbole(symboleTable);
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
	if(symbole.count(nameFunction) >= 1)
		throw std::invalid_argument("Name of function already " + nameFunction + " exist");
	Type* returnType = new PrimitiveType(typeNode.getName());
	FunctionType* type = new FunctionType(*returnType);
	Type* tmp;
	for(Node* n : allParameter)
		if(tmp = n->getType())
			type->addParameter(tmp);
	symbole[nameFunction] = type;
}
void Function::createSymboleTable(void)
{
	bodyNode.createSymboleTable();
}
