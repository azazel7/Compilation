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
Type const* PrimaryExpressionIdentifier::getType()
{
	return StackSymboleTable::getSymbole(name);
}
void PrimaryExpressionIdentifier::generateCode(FILE * fd) const
{
	fprintf(fd, "# put %s into the stack\n", name.c_str());
	fprintf(fd, "%s", StackSymboleTable::putLocationInto(name, "%eax").c_str());
	fprintf(fd, "push (%%eax)\n");
}
void PrimaryExpressionIdentifier::generateFloatingCode(FILE * fd, bool convert) const
{
	this->generateCode(fd);
	if(convert)
		fprintf(fd, "%s", convertToInteger().c_str());
}
