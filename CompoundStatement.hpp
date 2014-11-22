#ifndef COMPOUND_STATEMENT_HPP 
#define COMPOUND_STATEMENT_HPP
#include "Node.hpp"

class CompoundStatement : public Node
{
	public:
		CompoundStatement();
		CompoundStatement(int id);
		CompoundStatement(std::string name, int id = -1);
		void flattenStatement(void);
};
#endif 

