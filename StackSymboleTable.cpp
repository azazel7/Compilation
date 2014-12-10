#include "StackSymboleTable.hpp"

std::list<std::map<std::string, Type*> > StackSymboleTable::stack;

void StackSymboleTable::push(std::map<std::string, Type*> table)
{
	stack.push_front(table);
}
void StackSymboleTable::pop(void)
{
	stack.pop_front();
	//TODO think about delete Type* at the end
}
Type* StackSymboleTable::getSymbole(std::string name)
{
	for(auto table : stack)
		if(table.count(name) == 1)
			return table[name];
	return nullptr;
}
