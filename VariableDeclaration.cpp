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
