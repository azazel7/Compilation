#include "ExpressionStatement.hpp"


ExpressionStatement::ExpressionStatement(Node& expression):Node(), expression(expression)
{
}
void ExpressionStatement::semanticsCheck(void) const
{
	expression.semanticsCheck();
}
void ExpressionStatement::generateCode(FILE * fd) const
{
	expression.generateCode(fd);
	fprintf(fd, "pop %%eax\n");//Because each expression push its result
}
