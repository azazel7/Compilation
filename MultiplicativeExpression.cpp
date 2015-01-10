#include "MultiplicativeExpression.hpp"
#include <stdexcept>
#include "TypeOperationConversion.hpp"

MultiplicativeExpression::MultiplicativeExpression(Node& r, Node& l): Node(ID_MULTIPLICATIVE), right(r), left(l)
{
}
void MultiplicativeExpression::semanticsCheck(void) const
{
	right.semanticsCheck();
	left.semanticsCheck();
	Type const* tRight = right.getType();
	Type const* tLeft = left.getType();
	if(!tRight || !tLeft)
		throw std::invalid_argument("Error: a type is null");
	if(!TypeOperationConversion::getTypeOperation(OPERATION_BY, *tRight, *tLeft))
		throw std::invalid_argument("Error with this operation and those type");
}
Type const* MultiplicativeExpression::getType()
{
	Type const* tRight = right.getType();
	Type const* tLeft = left.getType();
	//TODO hope neither tRight, nor tLeft will be null
	return TypeOperationConversion::getTypeOperation(OPERATION_BY, *tRight, *tLeft);
}

void MultiplicativeExpression::generateCode(FILE * fd) const
{
	generateSubCode(fd, right, left);
	fprintf(fd, "; Multiplicative expression\n");
	fprintf(fd, "pop %%ebx\n");
	fprintf(fd, "pop %%eax\n");
	fprintf(fd, "imul %%ebx, %%eax\n");//TODO What about floating number ?
	fprintf(fd, "push %%eax\n");
}
void MultiplicativeExpression::generateFloatingCode(FILE * fd, bool convert) const
{
	right.generateFloatingCode(fd);
	left.generateFloatingCode(fd);
	fprintf(fd, "; Multiplicative expression (floating)\n");
	fprintf(fd, "movss (%%ebp), %%xmm1\n");
	fprintf(fd, "pop %%ebx\n");
	fprintf(fd, "movss (%%ebp), %%xmm0\n");
	fprintf(fd, "pop %%eax\n");
	fprintf(fd, "mulss %%xmm1, %%xmm0\n");
	fprintf(fd, "movd %%xmm0, %%eax\n");
	fprintf(fd, "push %%eax\n");
	if(convert)
		fprintf(fd, "%s", convertToInteger().c_str());
}
MultiplicativeExpression::~MultiplicativeExpression()
{
	delete &right;
	delete &left;
}
