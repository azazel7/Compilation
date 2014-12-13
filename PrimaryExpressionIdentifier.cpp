#include "PrimaryExpressionIdentifier.hpp"
#include <stdexcept>
#include "StackSymboleTable.hpp"

PrimaryExpressionIdentifier::PrimaryExpressionIdentifier(std::string name) : Node(ID_IDENTIFIER)
{
	this->name = name;
}
void PrimaryExpressionIdentifier::semanticsCheck(void) const
{
	if(StackSymboleTable::getSymbole(name) == nullptr)
		throw std::invalid_argument("Name doesn't exist : " + name);
}
Type* PrimaryExpressionIdentifier::getType()
{
	return StackSymboleTable::getSymbole(name);
}
