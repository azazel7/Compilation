#include "ForStatement.hpp"

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
	std::string id = "rand string";
	expressionInit.generateCode(fd);
	
	fprintf(fd, "%s:\n", id.c_str());//Write label
	expressionCondition.generateCode(fd);
	fprintf(fd, "pop %%eax\n");
	fprintf(fd, "cmp %%eax, $1\n");
	fprintf(fd, "jne %send\n", id.c_str());
	statement.generateCode(fd);
	expressionVariation.generateCode(fd);
	//TODO probably add a pop here
	fprintf(fd, "jmp %s\n", id.c_str());
	fprintf(fd, "%send:\n", id.c_str());//Write label
}
