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
	if(isGlobalSymbole(name))
		return "$" + getGlobalLabel(name);//The $ is here to manipulate labels
	for(auto table : stackLocation)
		if(table.count(name) == 1)
			return table[name];
	throw std::invalid_argument("Can't find symbole " + name + " in getLocation");
}
std::string StackSymboleTable::getLocation(std::string name, std::string registerOffset)
{
	return " ";
}

void StackSymboleTable::push(std::map<std::string, Type const*> table, std::map<std::string, std::string> location)
{
	stackLocation.push_front(location);
	StackSymboleTable::push(table);
}

bool StackSymboleTable::isGlobalSymbole(std::string const name)
{
	return stack.back().count(name) == 1;
}

std::string StackSymboleTable::getGlobalLabel(std::string const name)
{
	return "1_" + name;
}
std::string StackSymboleTable::randomString(const int size)
{
	std::string ret;
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	static const int stringLength = sizeof(alphanum) - 1;
	for(int i = 0; i < size; i++)
	{
		ret += alphanum[rand() % stringLength];
	}
	return ret;
}
