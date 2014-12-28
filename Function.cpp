#include "Function.hpp"
#include <stdexcept>
#include "FunctionType.hpp"
#include "PrimitiveType.hpp"
#include "StackSymboleTable.hpp"
#include "VariableDeclaration.hpp"
#include "PointerType.hpp"

Function::Function(Node* type, Node* argument, Node* body) : Node(ID_FUNCTION), typeNode(*type), bodyNode(*body)
{
	argument->getNodeById(allParameter, ID_PARAMETER);
	nameFunction = argument->getName();
	//TODO does argument is useful now ?
}

void Function::print(void)
{
	std::cout << typeNode.getName() << " " << nameFunction << " (";
	for(Node* n : allParameter)
		n->print();
	std::cout << ")" << std::endl;
	bodyNode.print();

}
void Function::semanticsCheck(void) const
{
	StackSymboleTable::push(symboleTable);
	bodyNode.semanticsCheck();
	StackSymboleTable::pop();
}

void Function::getSymbole(std::map<std::string, Type const*> & symbole) const
{
	std::string name = nameFunction;
	if(symbole.count(nameFunction) >= 1)
		throw std::invalid_argument("Name of function already " + nameFunction + " exist");
	Type* returnType = new PrimitiveType(typeNode.getName());
	if(VariableDeclaration::isPointedId(nameFunction))
	{
		name.erase(name.begin());
		returnType = new PointerType(*returnType);
	}
	FunctionType* type = new FunctionType(*returnType);
	Type const* tmp;
	for(Node* n : allParameter)
		if(tmp = n->getType())
			type->addParameter(tmp);
	symbole[name] = type;
}
void Function::createSymboleTable(void)
{
	for(Node* n : allParameter)
		n->getSymbole(symboleTable);
	bodyNode.getSymbole(symboleTable);
	int currentOffset = 0;
	for(auto symbole : symboleTable)
	{
		offsetTable[symbole.first] = currentOffset;//TODO change that into a location table
		currentOffset += symbole.second->getSize();
	}
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
void Function::generateCode(FILE * fd) const
{
	//TODO StackSymboleTable push symboles and locations
	StackSymboleTable::push(symboleTable);
	int sizeAllSymbole = 0;
	
	std::string label = StackSymboleTable::getGlobalLabel(nameFunction);
	fprintf(fd, "%s:\n", label.c_str());
	fprintf(fd, "push %%ebp\n");
	fprintf(fd, "mov %%esp, %%ebp\n");
	if(sizeAllSymbole > 0)
		fprintf(fd, "sub $%d, %%esp\n", sizeAllSymbole);
	bodyNode.generateCode(fd);
	fprintf(fd, "leave\n");//leave = move ebp, esp + pop ebp
	fprintf(fd, "ret\n");
	//TODO StackSymboleTable pop symboles and locations
	StackSymboleTable::pop();
}
