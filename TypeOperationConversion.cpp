#include "TypeOperationConversion.hpp"

std::map<char, std::map<char, std::map<char, char>>> TypeOperationConversion::table;

Type* TypeOperationConversion::getTypeOperation(char operation, Type& t1, Type& t2)
{
	//TODO Find a way to do it. I have no ideas.
	return nullptr;
}
void TypeOperationConversion::initTable(void)
{
	std::map<char, char> loutre;
	std::map<char, std::map<char, char> > canard;

	//ADD operation
	loutre[POINTER_TYPE] = POINTER_TYPE;
	loutre[INT_TYPE] = INT_TYPE;
	loutre[FLOAT_TYPE] = INT_TYPE;
	canard[INT_TYPE] = loutre;
	loutre.clear();

	loutre[INT_TYPE] = INT_TYPE;
	loutre[FLOAT_TYPE] = FLOAT_TYPE;
	canard[FLOAT_TYPE] = loutre;
	loutre.clear();

	loutre[POINTER_TYPE] = POINTER_TYPE;
	loutre[INT_TYPE] = POINTER_TYPE;
	canard[POINTER_TYPE] = loutre;
	loutre.clear();

	loutre.clear();
	table[OPERATION_ADD] = canard;

	//SUB operation
	loutre[POINTER_TYPE] = POINTER_TYPE;
	loutre[INT_TYPE] = INT_TYPE;
	loutre[FLOAT_TYPE] = INT_TYPE;
	canard[INT_TYPE] = loutre;
	loutre.clear();

	loutre[INT_TYPE] = INT_TYPE;
	loutre[FLOAT_TYPE] = FLOAT_TYPE;
	canard[FLOAT_TYPE] = loutre;
	loutre.clear();

	loutre[POINTER_TYPE] = POINTER_TYPE;
	loutre[INT_TYPE] = POINTER_TYPE;
	canard[POINTER_TYPE] = loutre;
	loutre.clear();

	loutre.clear();
	table[OPERATION_SUB] = canard;

	//BY operation
	loutre[INT_TYPE] = INT_TYPE;
	loutre[FLOAT_TYPE] = INT_TYPE;
	canard[INT_TYPE] = loutre;
	loutre.clear();

	loutre[INT_TYPE] = INT_TYPE;
	loutre[FLOAT_TYPE] = FLOAT_TYPE;
	canard[FLOAT_TYPE] = loutre;
	loutre.clear();

	table[OPERATION_BY] = canard;

	//DIV operation
	loutre[INT_TYPE] = INT_TYPE;
	loutre[FLOAT_TYPE] = INT_TYPE;
	canard[INT_TYPE] = loutre;
	loutre.clear();

	loutre[INT_TYPE] = INT_TYPE;
	loutre[FLOAT_TYPE] = FLOAT_TYPE;
	canard[FLOAT_TYPE] = loutre;
	loutre.clear();

	table[OPERATION_DIV] = canard;
}
