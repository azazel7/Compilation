#pragma once
#include <map>
#include <list>
#include <string>

class Type;

class StackSymboleTable
{
	static std::list<std::map<std::string, Type const*> > stack;
	static std::list<std::map<std::string, int> > stackLocation;
	public:
	static void push(std::map<std::string, Type const*> table);
	static void push(std::map<std::string, Type const*> table, std::map<std::string, int> location);
	static void pop(void);
	static Type const* getSymbole(std::string name);
	static std::string randomString(const int size = 7);
	static bool isGlobalSymbole(std::string const name);
	static std::string putLocationInto(std::string name,std::string registerWanted);
	static std::string putLocationInto(std::string name,std::string registerWanted, std::string registerOffset);
	static std::string getGlobalLabel(std::string const name);
	
};
