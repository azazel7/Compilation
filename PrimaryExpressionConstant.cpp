#include "PrimaryExpressionConstant.hpp"
#include <iostream>
#include <stdexcept>
#include "StackSymboleTable.hpp"
#include "PrimitiveType.hpp"

PrimaryExpressionConstant::PrimaryExpressionConstant(std::string value, char ty): Node(ID_CONSTANTE)
{
	this->value = value;
	if(ty == CONSTANT_FLOAT)
		this->type = new PrimitiveType(PrimitiveType::float_type);	
	else
		this->type = new PrimitiveType(PrimitiveType::int_type);	
		
}
void PrimaryExpressionConstant::semanticsCheck(void) const
{
}
Type const* PrimaryExpressionConstant::getType()
{
	return type;
}

PrimaryExpressionConstant::~PrimaryExpressionConstant()
{
	delete type;
}
