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
	right.generateCode(fd);
	left.generateCode(fd);
	fprintf(fd, "pop %%ecx\n");
	fprintf(fd, "pop %%ebx\n");
	fprintf(fd, "cmp %%ecx, %%ebx\n");
	fprintf(fd, "xor %%eax, %%eax\n");
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
