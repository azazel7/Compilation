#include "ComparisonExpression.hpp"
#include <sstream> 
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
void ComparisonExpression::semanticsCheck(void)
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
	fprintf(fd, "# Comparison expression\n");
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
	right.generateFloatingCode(fd);
	left.generateFloatingCode(fd);
	static int number = -1;
	number++;
	std::string id = "_comparison_expression";
	std::stringstream stringStream;
	stringStream << id << number;
	id = stringStream.str();
	fprintf(fd, "# Comparison expression (floating)\n");
	fprintf(fd, "movss (%%esp), %%xmm1\n");
	fprintf(fd, "pop %%eax\n");
	fprintf(fd, "movss (%%esp), %%xmm0\n");
	fprintf(fd, "pop %%eax\n");
	fprintf(fd, "ucomiss %%xmm1, %%xmm0\n");
	switch(typeOp)
	{
		case LE:
		fprintf(fd, "jg %s_1\n", id.c_str());
		break;
		case L:
		fprintf(fd, "jge %s_1\n", id.c_str());
		break;
		case GE:
		fprintf(fd, "jb %s_1\n", id.c_str());
		break;
		case G:
		fprintf(fd, "jbe %s_1\n", id.c_str());
		break;
		case EQ:
		fprintf(fd, "jne %s_1\n", id.c_str());
		break;
		case NE:
		fprintf(fd, "je %s_1\n", id.c_str());
		break;
	}
	fprintf(fd, "mov $1, %%eax\n");
	fprintf(fd, "jmp %s_2\n", id.c_str());
	fprintf(fd, "%s_1:\n", id.c_str());
	fprintf(fd, "xor %%eax, %%eax\n");
	fprintf(fd, "%s_2:\n", id.c_str());
	
	fprintf(fd, "push %%eax\n");
}
ComparisonExpression::~ComparisonExpression()
{
	delete &right;
	delete &left;
	delete type;
}
