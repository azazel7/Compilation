#include "TypeOperationConversion.hpp"

std::map<char, std::map<char, std::map<char, char>>> TypeOperationConversion::table;

Type* TypeOperationConversion::getTypeOperation(char operation, Type& t1, Type& t2)
{
	if(table.count(operation) == 0)
		return nullptr;
	std::map<char, std::map<char, char> > canard = table[operation];
	if(canard.count(t1.getType()) == 0)
		return nullptr;
	std::map<char, char> loutre = canard[t1.getType()];
	if(loutre.count(t2.getType()) == 0)
		return nullptr;
	if(loutre[t2.getType()])
		return &t2;
	return &t1;
}
void TypeOperationConversion::initTable(void)
{
	std::map<char, char> loutre;
	std::map<char, std::map<char, char> > canard;

	//ADD operation
	loutre[POINTER_TYPE] = 1;
	loutre[INT_TYPE] = 0;
	loutre[FLOAT_TYPE] = 0;
	canard[INT_TYPE] = loutre;
	loutre.clear();

	loutre[INT_TYPE] = 1;
	loutre[FLOAT_TYPE] = 0;
	canard[FLOAT_TYPE] = loutre;
	loutre.clear();

	loutre[INT_TYPE] = 0;
	canard[POINTER_TYPE] = loutre;
	loutre.clear();

	table[OPERATION_ADD] = canard;
	canard.clear();

	//SUB operation
	loutre[POINTER_TYPE] = 1;
	loutre[INT_TYPE] = 0;
	loutre[FLOAT_TYPE] = 1;
	canard[INT_TYPE] = loutre;
	loutre.clear();

	loutre[INT_TYPE] = 1;
	loutre[FLOAT_TYPE] = 0;
	canard[FLOAT_TYPE] = loutre;
	loutre.clear();

	loutre[INT_TYPE] = 0;
	canard[POINTER_TYPE] = loutre;
	loutre.clear();

	loutre.clear();
	table[OPERATION_SUB] = canard;
	canard.clear();

	//BY operation
	loutre[INT_TYPE] = 0;
	loutre[FLOAT_TYPE] = 1;
	canard[INT_TYPE] = loutre;
	loutre.clear();

	loutre[INT_TYPE] = 1;
	loutre[FLOAT_TYPE] = 0;
	canard[FLOAT_TYPE] = loutre;
	loutre.clear();

	table[OPERATION_BY] = canard;
	canard.clear();

	//DIV operation
	loutre[INT_TYPE] = 0;
	loutre[FLOAT_TYPE] = 1;
	canard[INT_TYPE] = loutre;
	loutre.clear();

	loutre[INT_TYPE] = 0;
	loutre[FLOAT_TYPE] = 0;
	canard[FLOAT_TYPE] = loutre;
	loutre.clear();

	table[OPERATION_DIV] = canard;
	canard.clear();

	loutre[INT_TYPE] = 0;
	canard[INT_TYPE] = loutre;
	loutre.clear();

	table[OPERATION_MINUS] = canard;
	canard.clear();

	loutre[INT_TYPE] = 0;
	canard[INT_TYPE] = loutre;
	loutre.clear();

	table[OPERATION_DIF] = canard;
	canard.clear();

	loutre[INT_TYPE] = 0;
	canard[INT_TYPE] = loutre;
	loutre.clear();

	loutre[POINTER_TYPE] = 0;
	canard[POINTER_TYPE] = loutre;
	loutre.clear();

	table[OPERATION_DEC] = canard;
	canard.clear();

	loutre[INT_TYPE] = 0;
	canard[INT_TYPE] = loutre;
	loutre.clear();

	loutre[POINTER_TYPE] = 0;
	canard[POINTER_TYPE] = loutre;
	loutre.clear();

	table[OPERATION_INC] = canard;
	canard.clear();
}
