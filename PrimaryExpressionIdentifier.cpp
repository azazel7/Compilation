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
	std::string location = StackSymboleTable::getLocation(name);
	fprintf(fd, "mov %s, %%eax\n", location.c_str());
	fprintf(fd, "push %%eax\n");
}
