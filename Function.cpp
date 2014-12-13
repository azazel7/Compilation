#include "Function.hpp"
#include <stdexcept>
#include "FunctionType.hpp"
#include "PrimitiveType.hpp"
#include "StackSymboleTable.hpp"

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
void Function::semanticsCheck(void) const
{
	StackSymboleTable::push(symboleTable);
	bodyNode.semanticsCheck();
	StackSymboleTable::pop();
}

void Function::getSymbole(std::map<std::string, Type*> & symbole) const
{
	//TODO enable for later, but now I'm too lazy to create a good c file to compile
	//if(symbole.count(nameFunction) >= 1)
		//throw std::invalid_argument("Name of function already " + nameFunction + " exist");
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
	for(Node* n : allParameter)
		n->getSymbole(symboleTable);
	bodyNode.createSymboleTable();
}
void Function::printSymboleTable(void) const
{
	std::cout <<"{" << std::endl;
	for(auto symbole : symboleTable)
	{
		std::cout << symbole.first << " ";
		symbole.second->print();
		std::cout << std::endl;
	}
	bodyNode.printSymboleTable();
	std::cout <<"}" << std::endl;
}
