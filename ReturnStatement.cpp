#include "ReturnStatement.hpp"

ReturnStatement::ReturnStatement(Node* l)
{
	expression = l;
}
void ReturnStatement::semanticsCheck(void)
{
	if(expression != nullptr)
		expression->semanticsCheck();
}
void ReturnStatement::generateCode(FILE * fd) const
{
	if(expression != nullptr)
	{
		expression->generateCode(fd);
		//FIXME size of the pop depend of expression type
		fprintf(fd, "# return\n");
		fprintf(fd, "pop %%eax\n");
	}
	else
		fprintf(fd, "# return\n");
	
	fprintf(fd, "leave\n");//leave = move ebp, esp + pop ebp
	fprintf(fd, "ret\n");
}
ReturnStatement::~ReturnStatement()
{
	if(expression != nullptr)
		delete expression;
}
