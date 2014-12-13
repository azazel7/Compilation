#include "VariableDeclaration.hpp"
#include "PrimitiveType.hpp"

VariableDeclaration::VariableDeclaration(Node* type, Node* identifier)
{
	this->type = type->getName();
	std::list<Node*> tmpId;
	if(identifier->getId() == ID_DECLARATOR)
	{
		tmpId.push_front(identifier);
	}
	else
	{
		identifier->getNodeById(tmpId, ID_DECLARATOR);
	}
	for(Node* n : tmpId)
	{
		id.push_front(n->getName());
		delete n;
	}
}
void VariableDeclaration::print(void)
{
	std::cout << type << " ";
	for(auto i : id)
		std::cout << i << ", ";
}
Type* VariableDeclaration::getType(void)
{
	return new PrimitiveType(type);
}
void VariableDeclaration::getSymbole(std::map<std::string, Type*> & symbole) const
{
	for(std::string name : id)
		if(symbole.count(name) == 0)
			symbole[name] = new PrimitiveType(type);
		//TODO enable for later, but now I'm too lazy to create a good c file to compile
		else
			throw std::invalid_argument("Variable " + name + " already exist");
}
