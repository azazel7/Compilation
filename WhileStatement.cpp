#include "WhileStatement.hpp"

WhileStatement::WhileStatement(Node& expression, Node& statement): expression(expression), statement(statement)
{
}
void WhileStatement::semanticsCheck(void) const
{
	expression.semanticsCheck();
	statement.semanticsCheck();
}
void WhileStatement::generateCode(FILE * fd) const
{
	std::string id = "rand string";
	
	fprintf(fd, "%s:\n", id.c_str());//Write label
	expression.generateCode(fd);
	fprintf(fd, "pop %%eax\n");
	fprintf(fd, "cmp %%eax, $1\n");
	fprintf(fd, "jne %send\n", id.c_str());
	statement.generateCode(fd);
	fprintf(fd, "jmp %s\n", id.c_str());
	fprintf(fd, "%send:\n", id.c_str());//Write label
}

