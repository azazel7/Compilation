#include "AdditiveExpression.hpp"
#include <stdexcept>
#include "TypeOperationConversion.hpp"

const char AdditiveExpression::sub = '-';
const char AdditiveExpression::add = '+';

AdditiveExpression::AdditiveExpression(Node& r, Node& l, char t): Node(ID_ADDITIVE), right(r), left(l)
{
	type = t;
}
void AdditiveExpression::semanticsCheck(void) const
{
	right.semanticsCheck();
	left.semanticsCheck();
	Type* tRight = right.getType();
	Type* tLeft = left.getType();
	if(!tRight || !tLeft)
		throw std::invalid_argument("Error: a type is null");
	if(!TypeOperationConversion::getTypeOperation(OPERATION_ADD, *tRight, *tLeft))
		throw std::invalid_argument("Error with this operation and those type");
}
Type* AdditiveExpression::getType()
{
	Type* tRight = right.getType();
	Type* tLeft = left.getType();
	//TODO hope neither tRight, nor tLeft will be null
	return TypeOperationConversion::getTypeOperation(OPERATION_ADD, *tRight, *tLeft);
}
