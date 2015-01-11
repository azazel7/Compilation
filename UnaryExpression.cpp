#include "UnaryExpression.hpp"
#include <stdexcept>
#include <sstream> 
#include "TypeOperationConversion.hpp"
#include "PrimitiveType.hpp"

const char UnaryExpression::neg = '-';
const char UnaryExpression::no = '!';
UnaryExpression::UnaryExpression(Node& l): Node(ID_UNARY_EXPRESSION), expression(l)
{
	typeUnarayExpression = new PrimitiveType(PrimitiveType::int_type);
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
	//TODO how do we call getType const from here ??
	if(type == neg)
		return expression.getType();
	return typeUnarayExpression;
}
Type const* UnaryExpression::getType() const
{
	if(type == neg)
		return expression.getType();
	return typeUnarayExpression;
}
void UnaryExpression::generateCode(FILE * fd) const
{
	//This if is for ! expression which return un int anyway
	if(expression.getType()->getType() == FLOAT_TYPE)
	{
		generateFloatingCode(fd);
		return;
	}
	else
		expression.generateCode(fd);
	
	fprintf(fd, "# Unary expression %c\n", type);
	fprintf(fd, "pop %%eax\n");
	switch(type)
	{
		case no:
			fprintf(fd, "mov %%eax, %%ebx\n");
			fprintf(fd, "xor %%eax, %%eax\n");
			fprintf(fd, "cmp $0, %%eax\n");
			fprintf(fd, "sete %%al\n");
		break;
		case neg:
		fprintf(fd, "neg %%eax\n");
		break;
	}
	fprintf(fd, "push %%eax\n");
}
void UnaryExpression::generateFloatingCode(FILE * fd, bool convert) const
{
	static int number = -1;
	number++;
	std::string id = "_comparison_expression";
	std::stringstream stringStream;
	stringStream << id << number;
	id = stringStream.str();

	expression.generateFloatingCode(fd);
	fprintf(fd, "# Unary expression %c (floating)\n", type);
	fprintf(fd, "movss (%%ebp), %%xmm0\n");
	fprintf(fd, "pop %%ebx\n");
	switch(type)
	{
		case no:
		fprintf(fd, "mov $0, %%eax\n");
		fprintf(fd, "push %%eax\n");
		fprintf(fd, "pxor %%xmm1, %%xmm1\n");
		fprintf(fd, "cvtsi2ssl (%%esp), %%xmm1\n");//Convert integer to fucking floating point
		fprintf(fd, "pop %%eax\n");
		fprintf(fd, "ucomiss %%xmm1, %%xmm0\n");
		fprintf(fd, "jne %s_1\n", id.c_str());
		fprintf(fd, "mov $1, %%eax\n");
		fprintf(fd, "jmp %s_2\n", id.c_str());
		fprintf(fd, "%s_1:\n", id.c_str());
		fprintf(fd, "xor %%eax, %%eax\n");
		fprintf(fd, "%s_2:\n", id.c_str());
		break;
		case neg:
		fprintf(fd, "mov $-1, %%eax\n");
		fprintf(fd, "push %%eax\n");
		fprintf(fd, "pxor %%xmm1, %%xmm1\n");
		fprintf(fd, "cvtsi2ssl (%%esp), %%xmm1\n");//Convert integer to fucking floating point
		fprintf(fd, "mulss %%xmm1, %%xmm0\n");
		fprintf(fd, "pop %%eax\n");
		fprintf(fd, "movd %%xmm0, %%eax\n");
		break;
	}
	fprintf(fd, "push %%eax\n");
	if(convert)
		fprintf(fd, "%s", convertToInteger().c_str());
}
UnaryExpression::~UnaryExpression()
{
	delete typeUnarayExpression;
	delete &expression;
}
