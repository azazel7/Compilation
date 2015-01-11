#include "PrimaryExpressionIdentifierOperation.hpp"
#include <stdexcept>
#include "StackSymboleTable.hpp"
#include "TypeOperationConversion.hpp"

const char PrimaryExpressionIdentifierOperation::dec = '+';
const char PrimaryExpressionIdentifierOperation::inc = '-';
PrimaryExpressionIdentifierOperation::PrimaryExpressionIdentifierOperation(std::string na, char type): Node(), type(type), name(na)
{
}
void PrimaryExpressionIdentifierOperation::semanticsCheck(void)
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
	fprintf(fd, "# %s %c%c\n", name.c_str(), type, type);
	fprintf(fd, "%s", StackSymboleTable::putLocationInto(name, "%%eax").c_str());
	fprintf(fd, "pushl (%%eax)\n");
	fprintf(fd, "mov (%%eax), %%ebx\n");
	if(type == inc)
		fprintf(fd, "add $1, %%ebx\n");
	else
		fprintf(fd, "sub $1, %%ebx\n");
	fprintf(fd, "mov %%ebx, (%%eax)\n");
}
void PrimaryExpressionIdentifierOperation::generateFloatingCode(FILE * fd, bool convert) const
{
	fprintf(fd, "# %s %c%c (floating)\n", name.c_str(), type, type);
	fprintf(fd, "%s", StackSymboleTable::putLocationInto(name, "%%eax").c_str());
	fprintf(fd, "pushl (%%eax)\n");
	fprintf(fd, "movss (%%eax), %%xmm0\n");
	if(type == inc)
		fprintf(fd, "mov $1, %%ebx\n");
	else
		fprintf(fd, "mov $-1, %%ebx\n");
	fprintf(fd, "pushl %%ebx\n");
	fprintf(fd, "pxor %%xmm1, %%xmm1\n");
	fprintf(fd, "cvtsi2ssl (%%esp), %%xmm1\n");//Convert integer to fucking floating point
	fprintf(fd, "popl %%ebx\n");
	fprintf(fd, "addss %%xmm1, %%xmm0\n");
	fprintf(fd, "movss %%xmm0, (%%eax)\n");
	if(convert)
		fprintf(fd, "%s", convertToInteger().c_str());
}
