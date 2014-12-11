#include "Expression.hpp"
#include <stdexcept>
#include "StackSymboleTable.hpp"
#include "Type.hpp"

Expression::Expression(std::string iden, Node& expr, Node* offset): Node(ID_EXPRESSION), id(iden), expression(expr)
{
	expressionOffset = offset;
}

void Expression::semanticsCheck(void) const
{
	Type* typeSymbole = StackSymboleTable::getSymbole(id);
	//TODO if typeSymbole is a pointer think about deference from this pointer
	if(typeSymbole == nullptr)
		throw std::invalid_argument("Can't find symbole");
	if(expressionOffset != nullptr)
	{
		Type* typeOffset = expressionOffset->getType();
		if(typeOffset->getType() != INT_TYPE)
		{
			throw std::invalid_argument("Error of index type expression");
		}
	}
	Type* typeExpression = expression.getType();
	if(!typeExpression || *typeExpression != *typeSymbole)
		throw std::invalid_argument("Id type != expression type");
	if(!expressionOffset)
		expressionOffset->semanticsCheck();
	expression.semanticsCheck();
}
Type* Expression::getType()
{
	//TODO probably an error here
	return StackSymboleTable::getSymbole(id);
};
