#include "ComparisonExpression.hpp"
#include "PrimitiveType.hpp"

const char ComparisonExpression::LE = 'a';
const char ComparisonExpression::L = 'b';
const char ComparisonExpression::GE = 'c';
const char ComparisonExpression::G = 'd';
const char ComparisonExpression::EQ = 'e';
const char ComparisonExpression::NE = 'f';

ComparisonExpression::ComparisonExpression(Node& r, Node &l, char t):Node(ID_COMPARISON), right(r), left(l) , typeOp(t)
{
	type = new PrimitiveType(PrimitiveType::int_type);
}
void ComparisonExpression::semanticsCheck(void) const
{
	right.semanticsCheck();
	left.semanticsCheck();
}
Type const* ComparisonExpression::getType()
{
	return type;
}
void ComparisonExpression::generateCode(FILE * fd) const
{
	if(left.getType()->getType() == FLOAT_TYPE && right.getType()->getType() == FLOAT_TYPE)
	{
		this->generateFloatingCode(fd);
		return;
	}
	else if(left.getType()->getType() == FLOAT_TYPE)
	{
		right.generateCode(fd);
		left.generateFloatingCode(fd, true);
	}
	else if(right.getType()->getType() == FLOAT_TYPE)
	{
		right.generateFloatingCode(fd, true);
		left.generateCode(fd);
	}
	else
	{
		right.generateCode(fd);
		left.generateCode(fd);
	}
	fprintf(fd, "; Comparison expression\n");
	fprintf(fd, "pop %%ecx\n");
	fprintf(fd, "pop %%ebx\n");
	fprintf(fd, "xor %%eax, %%eax\n");
	fprintf(fd, "cmp %%ecx, %%ebx\n");
	switch(typeOp)
	{
		case LE:
		fprintf(fd, "setle %%al\n");
		break;
		case L:
		fprintf(fd, "setl %%al\n");
		break;
		case GE:
		fprintf(fd, "setge %%al\n");
		break;
		case G:
		fprintf(fd, "setg %%al\n");
		break;
		case EQ:
		fprintf(fd, "sete %%al\n");
		break;
		case NE:
		fprintf(fd, "setne %%al\n");
		break;
	}
	fprintf(fd, "push %%eax\n");
}
void ComparisonExpression::generateFloatingCode(FILE * fd, bool convert) const
{
	fprintf(fd, "; Comparison expression (floating) (not done)\n");
	right.generateFloatingCode(fd);
	left.generateFloatingCode(fd);
	//TODO code for floating point
}
ComparisonExpression::~ComparisonExpression()
{
	delete &right;
	delete &left;
	delete type;
}
