#include "ProgramNode.hpp"
#include "StackSymboleTable.hpp"

ProgramNode::ProgramNode():Node(ID_PROGRAM)
{
}
void ProgramNode::createSymboleTable(void)
{
	for(Node* child : children)
		child->getSymbole(symboleTable);
	for(Node* child : children)
		child->createSymboleTable();
}
void ProgramNode::semanticsCheck(void) const
{
	StackSymboleTable::push(symboleTable);
	for(Node* child : children)
		child->semanticsCheck();
	StackSymboleTable::pop();
}
