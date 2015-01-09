#include "PrimaryExpressionArrayAccess.hpp"
#include <stdexcept>
#include "StackSymboleTable.hpp"
#include "PointerType.hpp"
#include "Type.hpp"

PrimaryExpressionArrayAccess::PrimaryExpressionArrayAccess(std::string id, Node& expression):id(id), expression(expression)
{
}
void PrimaryExpressionArrayAccess::semanticsCheck(void) const
{
	expression.semanticsCheck();
	PointerType const* typeId = dynamic_cast<PointerType const*>(StackSymboleTable::getSymbole(id));
	if(typeId == nullptr)
		throw std::invalid_argument("Error " + id + " doesn't exist or isn't an array (or pointer)");
	Type const* expressionType = expression.getType();
	if(expressionType->getType() != INT_TYPE)
		throw std::invalid_argument("Error expression isn't int type");
}
Type const* PrimaryExpressionArrayAccess::getType()
{
	PointerType const* typeId = dynamic_cast<PointerType const*>(StackSymboleTable::getSymbole(id));
	return typeId->getPointedType();	
}
void PrimaryExpressionArrayAccess::generateCode(FILE * fd) const
{
	expression.generateCode(fd);
	fprintf(fd, "pop %%ebx\n");
	fprintf(fd, "%s", StackSymboleTable::putLocationInto(id, "%%eax", "%%ebx").c_str());
	fprintf(fd, "push (%%eax)\n");
}
void PrimaryExpressionArrayAccess::generateFloatingCode(FILE * fd, bool convert) const
{
	expression.generateCode(fd);
	if(convert)
		fprintf(fd, "%s", convertToInteger().c_str());
}
PrimaryExpressionArrayAccess::~PrimaryExpressionArrayAccess()
{
	delete &expression;
}
