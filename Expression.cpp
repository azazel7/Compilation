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
}
