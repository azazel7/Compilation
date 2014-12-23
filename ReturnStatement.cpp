#include "ReturnStatement.hpp"

ReturnStatement::ReturnStatement(Node* l)
{
	expression = l;
}
void ReturnStatement::semanticsCheck(void) const
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
		fprintf(fd, "pop %%eax\n");
	}
	
	//FIXME probably create a goto to the label of the end of the conteining function
	fprintf(fd, "ret\n");
}
