#include "IfStatement.hpp"

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
