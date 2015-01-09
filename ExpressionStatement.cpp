#include "ExpressionStatement.hpp"
#include "Type.hpp"


ExpressionStatement::ExpressionStatement(Node& expression):Node(), expression(expression)
{
}
void ExpressionStatement::semanticsCheck(void) const
{
	expression.semanticsCheck();
}
void ExpressionStatement::generateCode(FILE * fd) const
{
	if(expression.getType()->getType() == FLOAT_TYPE)
		expression.generateFloatingCode(fd);
	else
		expression.generateCode(fd);
	fprintf(fd, "pop %%eax\n");//Because each expression push its result
}
