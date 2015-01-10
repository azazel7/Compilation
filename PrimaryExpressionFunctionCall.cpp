#include "PrimaryExpressionFunctionCall.hpp"
#include <stdexcept>
#include "StackSymboleTable.hpp"
#include "FunctionType.hpp"


PrimaryExpressionFunctionCall::PrimaryExpressionFunctionCall(std::string id, std::list<Node*> argumentList)
{
	this->id = id;
	this->argumentList = argumentList;
}
void PrimaryExpressionFunctionCall::semanticsCheck(void) const
{
	for(Node* node : argumentList)
		node->semanticsCheck();
	Type const* type = StackSymboleTable::getSymbole(id);
	if(type == nullptr)
		throw std::invalid_argument("Cannot find symbol " + id);
	FunctionType const* typeFunction = dynamic_cast<FunctionType const*>(type);
	if(typeFunction == nullptr)
		throw std::invalid_argument(id + " isn't a function it's " + type->getString());
		
	//FIXME it will be the same pointer, probably delete twice
	FunctionType* typeCompare = new FunctionType(*typeFunction->getReturnType());
	//FIXME remember, type returned by getType are forbidden from deletion ! And typeCompare will probably delete them
	for(Node* node : argumentList)
		typeCompare->addParameter(node->getType());
	if(*typeCompare != *type)
		throw std::invalid_argument("Error in arguments type when calling " + id);
		
}
Type const* PrimaryExpressionFunctionCall::getType()
{
	FunctionType const* type = dynamic_cast<FunctionType const*>(StackSymboleTable::getSymbole(id));
	return type->getReturnType();
}
PrimaryExpressionFunctionCall::~PrimaryExpressionFunctionCall()
{
	for(Node* node : argumentList)
		delete node;
}
void PrimaryExpressionFunctionCall::generateCode(FILE * fd) const
{
	fprintf(fd, "; Function call\n");
	for(Node* argument : argumentList) 
	{
		if(argument->getType()->getType() == FLOAT_TYPE)
			argument->generateFloatingCode(fd); //Each argument will push itself to the stack
		else
			argument->generateCode(fd); //Each argument will push itself to the stack
	}

	fprintf(fd, "call %s\n", StackSymboleTable::getGlobalLabel(id).c_str());

	fprintf(fd, "; Remove arg of function call\n");
	for(Node* argument : argumentList)//TODO pop the good size ... -_-"
		fprintf(fd, "pop %%ebx\n"); //Pop all arguments
	
	fprintf(fd, "; Push result of function call\n");
	fprintf(fd, "push  %%eax\n");//Because the result of the function is in %eax
}
void PrimaryExpressionFunctionCall::generateFloatingCode(FILE * fd, bool convert) const
{
	this->generateCode(fd);
	if(convert)
		fprintf(fd, "%s", convertToInteger().c_str());
}
