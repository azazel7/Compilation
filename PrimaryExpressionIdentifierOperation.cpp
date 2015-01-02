#include "PrimaryExpressionIdentifierOperation.hpp"
#include <stdexcept>
#include "StackSymboleTable.hpp"
#include "TypeOperationConversion.hpp"

const char PrimaryExpressionIdentifierOperation::dec = '+';
const char PrimaryExpressionIdentifierOperation::inc = '-';
PrimaryExpressionIdentifierOperation::PrimaryExpressionIdentifierOperation(std::string na, char type): Node(), type(type), name(na)
{
}
void PrimaryExpressionIdentifierOperation::semanticsCheck(void) const
{
	Type const* type = StackSymboleTable::getSymbole(name);
	if( type == nullptr)
		throw std::invalid_argument(name + " doesn't exist");
	//TODO daughter class will call this function and also check if operation is permitted
}
Type const* PrimaryExpressionIdentifierOperation::getType()
{
	return StackSymboleTable::getSymbole(name);
}
void PrimaryExpressionIdentifierOperation::generateCode(FILE * fd) const
{
	fprintf(fd, "%s", StackSymboleTable::putLocationInto(name, "%%eax").c_str());
	fprintf(fd, "push (%%eax)\n");
	fprintf(fd, "mov (%%eax), %%ebx\n");
	if(type == inc)
		fprintf(fd, "add $1, %%ebx\n");
	else
		fprintf(fd, "sub $1, %%ebx\n");
	fprintf(fd, "mov %%ebx, (%%eax)\n");
}
