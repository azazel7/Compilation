#include "PrimaryExpressionIdentifierOperation.hpp"
#include <stdexcept>
#include "StackSymboleTable.hpp"
#include "TypeOperationConversion.hpp"

PrimaryExpressionIdentifierOperation::PrimaryExpressionIdentifierOperation(std::string na)
{
	name = na;
}
void PrimaryExpressionIdentifierOperation::semanticsCheck(void) const
{
	Type* type = StackSymboleTable::getSymbole(name);
	if( type == nullptr)
		throw std::invalid_argument(name + " doesn't exist");
	//TODO daughter class will call this function and also check if operation is permitted
}
Type* PrimaryExpressionIdentifierOperation::getType()
{
	return StackSymboleTable::getSymbole(name);
}
