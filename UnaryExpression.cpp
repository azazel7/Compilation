#include "UnaryExpression.hpp"
#include <stdexcept>
#include "TypeOperationConversion.hpp"

UnaryExpression::UnaryExpression(Node& l): Node(ID_UNARY_EXPRESSION), expression(l)
{
}
void UnaryExpression::semanticsCheck(void) const
{
	expression.semanticsCheck();
	Type const* tRight = expression.getType();
	if(tRight == nullptr)
		throw std::invalid_argument("Error: a type is null");
	if(TypeOperationConversion::getTypeOperation(OPERATION_BY, *tRight, *tRight) == nullptr)
		throw std::invalid_argument("Error: can't do unary operation on that kind of type");
}
Type const* UnaryExpression::getType()
{ 
	return expression.getType();
}


