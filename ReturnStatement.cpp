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
