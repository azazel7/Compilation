#include "StackSymboleTable.hpp"
#include <stdexcept>

std::list<std::map<std::string, Type const*> > StackSymboleTable::stack;
std::list<std::map<std::string, std::string> > StackSymboleTable::stackLocation;

void StackSymboleTable::push(std::map<std::string, Type const*> table)
{
	stack.push_front(table);
}
void StackSymboleTable::pop(void)
{
	stack.pop_front();
	//TODO think about delete Type* at the end
	if(stackLocation.size() > 0)
		stackLocation.pop_front();
}
Type const* StackSymboleTable::getSymbole(std::string name)
{
	for(auto table : stack)
		if(table.count(name) == 1)
			return table[name];
	return nullptr;
}
std::string StackSymboleTable::getLocation(std::string name)
{
	for(auto table : stackLocation)
		if(table.count(name) == 1)
			return table[name];
	throw std::invalid_argument("Can't find symbole " + name + " in getLocation");
}

void StackSymboleTable::push(std::map<std::string, Type const*> table, std::map<std::string, std::string> location)
{
	stackLocation.push_front(location);
	StackSymboleTable::push(table);
}
