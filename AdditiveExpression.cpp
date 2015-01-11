#include "AdditiveExpression.hpp"
#include <stdexcept>
#include "TypeOperationConversion.hpp"
#include "PrimitiveType.hpp"

const char AdditiveExpression::sub = '-';
const char AdditiveExpression::add = '+';

AdditiveExpression::AdditiveExpression(Node& r, Node& l, char t): Node(ID_ADDITIVE), right(r), left(l)
{
	type = t;
}
void AdditiveExpression::semanticsCheck(void)
{
	right.semanticsCheck();
	left.semanticsCheck();
	Type const* tRight = right.getType();
	Type const* tLeft = left.getType();
	if(!tRight || !tLeft)
		throw std::invalid_argument("Error: a type is null");
	if(!TypeOperationConversion::getTypeOperation(OPERATION_ADD, *tRight, *tLeft))
		throw std::invalid_argument("Error with this operation and those type");
}
Type const* AdditiveExpression::getType()
{
	//hope neither tRight, nor tLeft will be null
	//I don't think so, because semanticsCheck of right and left is executed before
	Type const* tRight = right.getType();
	Type const* tLeft = left.getType();
	return TypeOperationConversion::getTypeOperation(OPERATION_ADD, *tRight, *tLeft);
}
void AdditiveExpression::generateCode(FILE * fd) const
{
	generateSubCode(fd, right, left);
	fprintf(fd, "# Additive expression\n");
	fprintf(fd, "pop %%ebx\n");
	fprintf(fd, "pop %%eax\n");
	switch(type)
	{
		case sub:
		fprintf(fd, "sub %%ebx, %%eax\n");
		break;
		case add:
		fprintf(fd, "add %%ebx, %%eax\n");
		break;
	}
	fprintf(fd, "push %%eax\n");
}
void AdditiveExpression::generateFloatingCode(FILE * fd, bool convert) const
{
	right.generateFloatingCode(fd);
	left.generateFloatingCode(fd);
	fprintf(fd, "# Additive expression (floating)\n");
	fprintf(fd, "movss (%%esp), %%xmm1\n");
	fprintf(fd, "pop %%ebx\n");
	fprintf(fd, "movss (%%esp), %%xmm0\n");
	fprintf(fd, "pop %%eax\n");
	switch(type)
	{
		case sub:
		fprintf(fd, "subss %%xmm1, %%xmm0\n");
		break;
		case add:
		fprintf(fd, "addss %%xmm1, %%xmm0\n");
		break;
	}
	fprintf(fd, "movd %%xmm0, %%eax\n");
	fprintf(fd, "push %%eax\n");
	if(convert)
		fprintf(fd, "%s", convertToInteger().c_str());
}
AdditiveExpression::~AdditiveExpression()
{
	delete &right;
	delete &left;
}
