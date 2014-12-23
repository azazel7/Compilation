#include "IfStatement.hpp"
#include <stdio.h>

IfStatement::IfStatement(Node& expression, Node& statement, Node* elseStatement): expression(expression), statement(statement)
{
	this->elseStatement = elseStatement;
}
void IfStatement::semanticsCheck(void) const
{
	expression.semanticsCheck();
	statement.semanticsCheck();
	if(elseStatement != nullptr)
		elseStatement->semanticsCheck();
}
void IfStatement::generateCode(FILE * fd) const
{
	std::string id = "rand string";
	expression.generateCode(fd);
	fprintf(fd, "pop %%eax\n");
	fprintf(fd, "cmp %%eax, $1\n");
	fprintf(fd, "jne %s\n", id.c_str());
	statement.generateCode(fd);
	if(elseStatement != nullptr)
		fprintf(fd, "jmp %send\n", id.c_str());
	
	fprintf(fd, "%s:\n", id.c_str());//Write label
	if(elseStatement != nullptr)
	{
		elseStatement->generateCode(fd);
		fprintf(fd, "%send:\n", id.c_str());//Write label
	}
	
}
