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
	Type const* type = StackSymboleTable::getSymbole(id);
	if(type == nullptr)
		throw std::invalid_argument("Cannot find symbol " + id);
	FunctionType const* typeFunction = dynamic_cast<FunctionType const*>(type);
	if(typeFunction == nullptr)
		throw std::invalid_argument(id + " isn't a function");
		
	for(Node* node : argumentList)
		node->semanticsCheck();
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
