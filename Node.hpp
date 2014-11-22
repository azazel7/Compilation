#ifndef NODE_HPP 
#define NODE_HPP 
#include <iostream>
#include <list>

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
class Node
{
	protected:
	std::list<Node*> children;
	int id = -1;
	void getNodeById(std::list<Node*> &listToFill, int id);
	void deleteAllChildFromId(int id);
	public:
	std::string name;
		Node();
		Node(int id);
		Node(std::string name, int i = -1);
		~Node();
		void addChild(Node& node);
		void print(void);
		void printTree(int deepth, int maxDeepth = -1);
		void flattenFunction(void);
		virtual void flattenStatement(void);
		void setId(int id);
};
//TODO TO THINK No need to flatten declarator_list -> just convert it into a symbols table 
#endif
