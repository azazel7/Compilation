#include "VariableDeclaration.hpp"
#include "PrimitiveType.hpp"
#include "PointerType.hpp"

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
bool VariableDeclaration::isPointedId(std::string id) const
{
	if(id.size() >= 2 && id[0] == '*')
		return true;
	return false;
}
Type* VariableDeclaration::getType(void)
{
	return new PrimitiveType(type);
}
void VariableDeclaration::getSymbole(std::map<std::string, Type const*> & symbole) const
{
	for(std::string name : id)
	{
		if(symbole.count(name) == 0)
		{
			Type* tmpType = new PrimitiveType(type);
			if(isPointedId(name))
			{
				tmpType = new PointerType(*tmpType);
				name.erase(name.begin());
				std::cout << "Pointed var " << name << std::endl;
			}
			symbole[name] = tmpType;
		}
		else
		{
			throw std::invalid_argument("Variable " + name + " already exist");
		}
	}
}
