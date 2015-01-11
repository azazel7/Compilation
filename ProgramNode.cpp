#include "ProgramNode.hpp"
#include <stdexcept>
#include "StackSymboleTable.hpp"
#include "FunctionType.hpp"
#include "PrimitiveType.hpp"
#include "PointerType.hpp"

const std::string ProgramNode::main_name = "main";

ProgramNode::ProgramNode():Node(ID_PROGRAM)
{
	//TODO add 2 symboles for printint and printfloat
	FunctionType* f = new FunctionType(*(new PrimitiveType(PrimitiveType::void_type)));
	f->addParameter(new PrimitiveType(PrimitiveType::int_type));
	symboleTable["printint"] = f;
	f = new FunctionType(*(new PrimitiveType(PrimitiveType::void_type)));
	f->addParameter(new PrimitiveType(PrimitiveType::float_type));
	symboleTable["printfloat"] = f;
	f = new FunctionType(*(new PointerType(*(new PrimitiveType(PrimitiveType::int_type)))));
	f->addParameter(new PrimitiveType(PrimitiveType::int_type));
	symboleTable["malloc_int"] = f;
	f = new FunctionType(*(new PointerType(*(new PrimitiveType(PrimitiveType::float_type)))));
	f->addParameter(new PrimitiveType(PrimitiveType::int_type));
	symboleTable["malloc_float"] = f;
}
void ProgramNode::createSymboleTable(void)
{
	for(Node* child : children)
		child->getSymbole(symboleTable);
	for(Node* child : children)
		child->createSymboleTable();
}
void ProgramNode::semanticsCheck(void)
{
	StackSymboleTable::push(symboleTable);
	for(Node* child : children)
		child->semanticsCheck();
	StackSymboleTable::pop();
	if(symboleTable.count(main_name) == 0)
		throw std::invalid_argument(std::string("function ") + main_name + " doesn't exist");
}
void ProgramNode::generateCode(FILE * fd) const
{
	StackSymboleTable::push(symboleTable);//No location table because global symboles can esealy be found
	fprintf(fd, ".data\n");
	for(Node* child : children)
		if(child->getId() != ID_FUNCTION)
			child->generateCode(fd);
	fprintf(fd, ".global %s\n", main_name.c_str());
	fprintf(fd, ".text\n");
	for(Node* child : children)
		if(child->getId() == ID_FUNCTION)
			child->generateCode(fd);
	StackSymboleTable::pop();
}
ProgramNode::~ProgramNode()
{
	for(auto sym : symboleTable)
		delete sym.second;
}
