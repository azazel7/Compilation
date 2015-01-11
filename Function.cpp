#include "Function.hpp"
#include <stdexcept>
#include "FunctionType.hpp"
#include "PrimitiveType.hpp"
#include "StackSymboleTable.hpp"
#include "VariableDeclaration.hpp"
#include "PointerType.hpp"
#include "IdentifierDeclarator.hpp"

Function::Function(Node* type, Node* argument, Node* body) : Node(ID_FUNCTION), typeNode(*type), bodyNode(*body)
{
	argument->getNodeById(allParameter, ID_PARAMETER);
	id = dynamic_cast<IdentifierDeclarator*>(argument);
}

void Function::print(void)
{
	std::cout << typeNode.getName() << " " << id->getName() << " (";
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
	std::string nameFunction = id->getName();
	if(symbole.count(nameFunction) >= 1)
		throw std::invalid_argument("Name of function already " + nameFunction + " exist");
	Type* returnType = new PrimitiveType(typeNode.getName());

	if(id->isPointed()) //When function return pointed type
		returnType = new PointerType(*returnType);
	else if(id->getSize() > 0)
		throw std::invalid_argument(nameFunction + " can not return a static array");

	FunctionType* type = new FunctionType(*returnType);
	Type const* tmp;
	
	//Add paramters
	for(Node* n : allParameter)
		if((tmp = n->getType()))
			type->addParameter(tmp);
	symbole[nameFunction] = type;
}
void Function::createSymboleTable(void)
{
	for(Node* n : allParameter)
		n->getSymbole(symboleTable);
	for(auto pair : symboleTable)//To separate argument of the function and other variable
		isParameter[pair.first] = true;
	bodyNode.getSymbole(symboleTable);
	for(auto e : symboleTable)
		std::cout << e.first << " ";
	std::cout << std::endl;
	int currentOffset = 0;
	int currentOffsetArg = 0;
	for(auto symbole : symboleTable)
	{
		//This if is for both kind of variable. The arguments of the function and the declared variables.
		if(isParameter.count(symbole.first) == 1)
		{
			offsetTable[symbole.first] = currentOffsetArg;
			currentOffsetArg += symbole.second->getSize();
		}
		else
		{
			currentOffset -= symbole.second->getSize();
			offsetTable[symbole.first] = currentOffset;
		}
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
	StackSymboleTable::push(symboleTable, offsetTable);
	int sizeAllSymbole = 0;
	//Count the size of the stack frame
	for(auto symbole : symboleTable)
		if(isParameter.count(symbole.first) == 0)
			sizeAllSymbole += symbole.second->getSize();
	
	std::string label = StackSymboleTable::getGlobalLabel(id->getName());
	fprintf(fd, "%s:\n", label.c_str());
	fprintf(fd, "push %%ebp\n");
	fprintf(fd, "mov %%esp, %%ebp\n");
	if(sizeAllSymbole > 0) //Create stackFrame
		fprintf(fd, "sub $%d, %%esp\n", sizeAllSymbole);
	bodyNode.generateCode(fd);
	fprintf(fd, "leave\n");//leave = move ebp, esp + pop ebp
	fprintf(fd, "ret\n");
	StackSymboleTable::pop();
}
Function::~Function()
{
	delete id;
	delete &typeNode;
	delete &bodyNode;
	for(Node* param : allParameter)
		delete param;
}
