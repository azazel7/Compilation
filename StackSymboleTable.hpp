#ifndef STACK_SYMBOLE_TABLE_HPP
#define STACK_SYMBOLE_TABLE_HPP
#include <map>
#include <list>
#include <string>

class Type;

class StackSymboleTable
{
	static std::list<std::map<std::string, Type const*> > stack;
	public:
	static void push(std::map<std::string, Type const*> table);
	static void pop(void);
	static Type const* getSymbole(std::string name);
	
};
#endif
