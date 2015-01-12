#include "ForStatement.hpp"
#include <sstream> 
#include <iostream>     // std::cout

ForStatement::ForStatement(Node& expressionInit, Node& expressionCondition, Node& expressionVariation, Node& statement): expressionInit(expressionInit), expressionCondition(expressionCondition), expressionVariation(expressionVariation), statement(statement)
{

}
void ForStatement::semanticsCheck(void) const
{
	expressionInit.semanticsCheck();
	expressionCondition.semanticsCheck();
	expressionVariation.semanticsCheck();
	statement.semanticsCheck();
}
void ForStatement::generateCode(FILE * fd) const
{
	static int number = -1;
	number++;
	std::string id = "_for_statement";
	std::stringstream stringStream;
	stringStream << id << number;
	id = stringStream.str();
	expressionInit.generateCode(fd);
	
	fprintf(fd, "%s:\n", id.c_str());//Write label
	expressionCondition.generateCode(fd);
	//fprintf(fd, "popl %%eax\n");//Useless because an expression_statement popl into eax, but we're not sure
	fprintf(fd, "mov $1, %%ebx\n");
	fprintf(fd, "cmp %%eax, %%ebx\n");
	fprintf(fd, "jne %send\n", id.c_str());
	statement.generateCode(fd);
	expressionVariation.generateCode(fd);
	fprintf(fd, "popl %%eax\n");//Useful because, expressionVariation isn't an expression_statement

	fprintf(fd, "jmp %s\n", id.c_str());
	fprintf(fd, "%send:\n", id.c_str());//Write label
}
ForStatement::~ForStatement()
{
	delete &expressionVariation;
	delete &expressionInit;
	delete &expressionCondition;
	delete &statement;
}
