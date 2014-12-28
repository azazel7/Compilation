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
void ProgramNode::generateCode(FILE * fd) const
{
	StackSymboleTable::push(symboleTable);//No location table because global symboles can esealy be found
	fprintf(fd, ".data\n");
	for(Node* child : children)
		if(child->getId() != ID_FUNCTION)
		{
			//TODO print label probably put them into VariableDeclaration
			fprintf(fd, ".byte");
			//Type const*
		}
	fprintf(fd, ".text\n");
	for(Node* child : children)
		if(child->getId() == ID_FUNCTION)
			child->generateCode(fd);
	StackSymboleTable::pop();
}
