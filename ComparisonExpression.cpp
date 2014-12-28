#include "ComparisonExpression.hpp"
#include "PrimitiveType.hpp"

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
		case COMPARISON_LE:
		fprintf(fd, "setle %%al\n");
		break;
		case COMPARISON_L:
		fprintf(fd, "setl %%al\n");
		break;
		case COMPARISON_GE:
		fprintf(fd, "setge %%al\n");
		break;
		case COMPARISON_G:
		fprintf(fd, "setg %%al\n");
		break;
		case COMPARISON_EQ:
		fprintf(fd, "sete %%al\n");
		break;
		case COMPARISON_NE:
		fprintf(fd, "setne %%al\n");
		break;
	}
	fprintf(fd, "push %%eax\n");
}
