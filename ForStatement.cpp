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
