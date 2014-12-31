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
Type const* PrimaryExpressionConstant::getType()
{
	return type;
}
void PrimaryExpressionConstant::generateCode(FILE * fd) const
{
	fprintf(fd, "mov $%s, %%eax\n", value.c_str());
	fprintf(fd, "push %%eax\n");
}

PrimaryExpressionConstant::~PrimaryExpressionConstant()
{
	delete type;
}
