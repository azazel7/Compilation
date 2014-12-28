#include "AdditiveExpression.hpp"
#include <stdexcept>
#include "TypeOperationConversion.hpp"

const char AdditiveExpression::sub = '-';
const char AdditiveExpression::add = '+';

AdditiveExpression::AdditiveExpression(Node& r, Node& l, char t): Node(ID_ADDITIVE), right(r), left(l)
{
	type = t;
}
void AdditiveExpression::semanticsCheck(void) const
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
	Type const* tRight = right.getType();
	Type const* tLeft = left.getType();
	//TODO hope neither tRight, nor tLeft will be null
	return TypeOperationConversion::getTypeOperation(OPERATION_ADD, *tRight, *tLeft);
}
void AdditiveExpression::generateCode(FILE * fd) const
{
	right.generateCode(fd);
	left.generateCode(fd);
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
