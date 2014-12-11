#include "MultiplicativeExpression.hpp"
#include <stdexcept>
#include "TypeOperationConversion.hpp"

MultiplicativeExpression::MultiplicativeExpression(Node& r, Node& l): Node(ID_MULTIPLICATIVE), right(r), left(l)
{
}
void MultiplicativeExpression::semanticsCheck(void) const
{
	right.semanticsCheck();
	left.semanticsCheck();
	Type* tRight = right.getType();
	Type* tLeft = left.getType();
	if(!tRight || !tLeft)
		throw std::invalid_argument("Error: a type is null");
	if(!TypeOperationConversion::getTypeOperation(OPERATION_BY, *tRight, *tLeft))
		throw std::invalid_argument("Error with this operation and those type");
}
Type* MultiplicativeExpression::getType()
{
	Type* tRight = right.getType();
	Type* tLeft = left.getType();
	//TODO hope neither tRight, nor tLeft will be null
	return TypeOperationConversion::getTypeOperation(OPERATION_BY, *tRight, *tLeft);
}

