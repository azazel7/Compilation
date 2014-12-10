#ifndef STACK_SYMBOLE_TABLE_HPP
#define STACK_SYMBOLE_TABLE_HPP
#include <map>
#include <list>
#include <string>

class Type;

class StackSymboleTable
{
	static std::list<std::map<std::string, Type*> > stack;
	public:
	static void push(std::map<std::string, Type*> table);
	static void pop(void);
	static Type* getSymbole(std::string name);
	
};
#endif
