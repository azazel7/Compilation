#include "StackSymboleTable.hpp"
#include <sstream>
#include <iostream>     // std::cout
#include <stdexcept>
#include <algorithm>
#include "PointerType.hpp"

std::list<std::map<std::string, Type const*> > StackSymboleTable::stack;
std::list<std::map<std::string, int> > StackSymboleTable::stackLocation;
std::list<std::string> StackSymboleTable::allFloatingNumber;

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
std::string StackSymboleTable::putLocationInto(std::string name, std::string registerWanted)
{
	std::stringstream stringStream;
	std::string location;
	if(isGlobalSymbole(name))
	{
		location = getGlobalLabel(name);
		stringStream << "mov " << location << ", " << registerWanted << std::endl;
		return stringStream.str();
	}
	for(auto table : stackLocation)
		if(table.count(name) == 1)
		{
			std::stringstream stringStream;
			stringStream << "mov $" << table[name] << ", " << registerWanted << std::endl;
			stringStream << "add %esp, " << registerWanted << std::endl;
			return stringStream.str();
		}
	throw std::invalid_argument("Can't find symbole " + name + " in putLocationInto");
}
std::string StackSymboleTable::putLocationInto(std::string name,std::string registerWanted, std::string registerOffset)
{
	std::stringstream stringStream;
	PointerType const* type = dynamic_cast<PointerType const*>(getSymbole(name));
	int size = type->getPointedType()->getSize();
	stringStream << putLocationInto(name, registerWanted);
	stringStream << "pushl " << registerOffset << std::endl;
	stringStream << "pushl " << registerWanted << std::endl;
	stringStream << "pushl " << registerOffset << std::endl;
	stringStream << "mov  $" << size << ", %eax" << std::endl;
	stringStream << "imul (%esp), %eax" << std::endl;
	stringStream << "popl %ebx" << std::endl;//Remove pushed registerOffset
	stringStream << "popl %ebx" << std::endl;//Store in ebx the init address of the symbole
	stringStream << "add %eax, %ebx" << std::endl;
	stringStream << "mov %ebx, " << registerWanted << std::endl;
	stringStream << "popl " << registerOffset << std::endl; //Put back registerOffset
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
	return name;
}
std::string StackSymboleTable::getLabelFloatingNumber(std::string name)
{
	std::replace(name.begin(), name.end(), '.', '_');
	return std::string("floating_number_") + name;
}
void StackSymboleTable::addFloatingNumber(std::string const name)
{
	auto it = std::find(allFloatingNumber.begin(), allFloatingNumber.end(), name);
	if(it != allFloatingNumber.end())
		return;
	allFloatingNumber.push_front(name);
}
void StackSymboleTable::writeFloatingNumber(FILE* fd)
{
	for(std::string f : allFloatingNumber)
		fprintf(fd, ".lcomm %s %s\n", getLabelFloatingNumber(f).c_str(), f.c_str());
}
