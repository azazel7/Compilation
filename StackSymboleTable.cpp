#include "StackSymboleTable.hpp"
#include <sstream> 
#include <iostream>     // std::cout
#include <stdexcept>
#include "PointerType.hpp"

std::list<std::map<std::string, Type const*> > StackSymboleTable::stack;
std::list<std::map<std::string, int> > StackSymboleTable::stackLocation;

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
		{
			std::stringstream stringStream;
			stringStream << table[name] << "(%ebp)";
			return stringStream.str();
		}
	throw std::invalid_argument("Can't find symbole " + name + " in getLocation");
}
std::string StackSymboleTable::getLocation(std::string name, std::string registerOffset)
{
	std::stringstream stringStream;
	int offset;
	for(auto table : stackLocation)
		if(table.count(name) == 1)
		{
			offset = offset;
			break;
		}
	PointerType const* type = dynamic_cast<PointerType const*>(getSymbole(name));
	//TODO what for global symbole ?
	stringStream << offset << "(%ebp," << registerOffset << "," <<  type->getPointedType()->getSize() <<  ")";
	return stringStream.str();
}

void StackSymboleTable::push(std::map<std::string, Type const*> table, std::map<std::string, int> location)
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
