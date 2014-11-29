#ifndef NODE_HPP 
#define NODE_HPP 
#include <iostream>
#include <list>
#include <map>
#include "Type.hpp"

#define ID_FUNCTION 1
#define ID_TYPE 2
#define ID_EXTERNAL_DECLARATION 3
#define ID_EXPRESSION 4
#define ID_DECLARATION 5
#define ID_DECLARATOR 6
#define ID_GLOBAL_DECLARATOR 7
#define ID_COUMPOUND_STATEMENT 8
#define ID_STATEMENT_LIST 9
#define ID_STATEMENT 10
#define ID_DECLARATION_LIST 11
#define ID_PARAMETER 12

#define ID_UNARY_EXPRESSION 13
#define ID_MULTIPLICATIVE 14
#define ID_ADDITIVE 15
#define ID_COMPARISON 16
#define ID_PARENTHESE_EXPRESSION 17
#define ID_IDENTIFIER 18
#define ID_CONSTANTE 19

class Type;

class Node
{
	protected:
	std::list<Node*> children;
	int id = -1;
	void deleteAllChildFromId(int id);
	std::string name;
	public:
		Node();
		Node(int id);
		Node(std::string name, int i = -1);
		~Node();
		void addChild(Node& node);
		virtual void print(void);
		void printTree(int deepth, int maxDeepth = -1);
		void flattenFunction(void);
		void getNodeById(std::list<Node*> &listToFill, int id);
		virtual void flattenStatement(void);
		virtual void flattenParameter(void);
		virtual void getSymbole(std::map<std::string, Type*> & symbole) const;
		virtual void createSymboleTable(void);
		virtual Type* getType(void);
		void setId(int id);
		int countChildren(void) const;
		std::string getName(void);
		int getId(void) const;
};
//TODO TO THINK No need to flatten declarator_list -> just convert it into a symbols table 
#endif
