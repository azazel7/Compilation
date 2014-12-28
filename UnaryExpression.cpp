#include "UnaryExpression.hpp"
#include <stdexcept>
#include "TypeOperationConversion.hpp"

const char UnaryExpression::neg = '-';
const char UnaryExpression::no = '!';
UnaryExpression::UnaryExpression(Node& l): Node(ID_UNARY_EXPRESSION), expression(l)
{
}
void UnaryExpression::semanticsCheck(void) const
{
	expression.semanticsCheck();
	Type const* tRight = expression.getType();
	if(tRight == nullptr)
		throw std::invalid_argument("Error: a type is null");
	if(TypeOperationConversion::getTypeOperation(OPERATION_BY, *tRight, *tRight) == nullptr)
		throw std::invalid_argument("Error: can't do unary operation on that kind of type");
}
Type const* UnaryExpression::getType()
{ 
	return expression.getType();
}

void UnaryExpression::generateCode(FILE * fd) const
{
	expression.generateCode(fd);
	fprintf(fd, "pop %%eax\n");
	switch(type)
	{
		case no:
			fprintf(fd, "mov %%eax, %%ebx\n");//TODO What about floating number ?
			fprintf(fd, "xor %%eax, %%eax\n");//TODO What about floating number ?
			fprintf(fd, "cmp $0, %%eax\n");//TODO What about floating number ?
			fprintf(fd, "sete %%al\n");//TODO What about floating number ?
		break;
		case neg:
		fprintf(fd, "neg %%eax\n");//TODO What about floating number ?
		break;
	}
	fprintf(fd, "push %%eax\n");
}

