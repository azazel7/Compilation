#include "Expression.hpp"
#include <iostream>
#include <stdexcept>
#include "StackSymboleTable.hpp"
#include "Type.hpp"
#include "PointerType.hpp"

Expression::Expression(std::string iden, Node& expr, Node* offset): Node(ID_EXPRESSION), id(iden), expression(expr)
{
	expressionOffset = offset;
}

void Expression::semanticsCheck(void) const
{
	if(expressionOffset != nullptr)
		expressionOffset->semanticsCheck();
	expression.semanticsCheck();

	Type const* typeSymbole = StackSymboleTable::getSymbole(id);
	//TODO if typeSymbole is a pointer think about deference from this pointer
	if(typeSymbole == nullptr)
		throw std::invalid_argument("Can't find symbole " + id);
	Type const* typeExpression = expression.getType();
	if(expressionOffset != nullptr)
	{
		Type const* typeOffset = expressionOffset->getType();
		PointerType const* pointedTypeSymbole= dynamic_cast<PointerType const*>(typeSymbole);
		if(pointedTypeSymbole == nullptr)
			throw std::invalid_argument(id + " must be a pointer or an array but is an" + typeSymbole->getString());
		if(typeOffset->getType() != INT_TYPE)
			throw std::invalid_argument("Error of index type expression : " + typeOffset->getString());
		typeSymbole = pointedTypeSymbole->getPointedType();
	}
	if(expressionOffset != nullptr)
	{}
		//TODO watch at the pointed type
	if(!typeExpression || *typeExpression != *typeSymbole)
		throw std::invalid_argument(typeSymbole->getString() + " != " + typeExpression->getString());
}
Type const* Expression::getType()
{
	//TODO probably an error here
	return StackSymboleTable::getSymbole(id);
};
