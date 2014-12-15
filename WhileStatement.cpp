#include "WhileStatement.hpp"

WhileStatement::WhileStatement(Node& expression, Node& statement): expression(expression), statement(statement)
{
}
void WhileStatement::semanticsCheck(void) const
{
	expression.semanticsCheck();
	statement.semanticsCheck();
}

