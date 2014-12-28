#include "VariableDeclaration.hpp"
#include <string>
#include "PrimitiveType.hpp"
#include "PointerType.hpp"
#include "IdentifierDeclarator.hpp"

VariableDeclaration::VariableDeclaration(Node* type, Node* identifier): Node(ID_DECLARATION)
{
	this->type = type->getName();
	delete type;
	std::list<Node*> tmpId;
	if(identifier->getId() == ID_DECLARATOR)
	{
		tmpId.push_front(identifier);
	}
	else
	{
		identifier->getNodeById(tmpId, ID_DECLARATOR);
		delete identifier;
	}
	
	for(Node* n : tmpId)
	{
		id.push_front(dynamic_cast<IdentifierDeclarator*>(n));
	}
}
void VariableDeclaration::print(void)
{
	std::cout << type << " ";
	for(auto i : id)
	{
		std::string isPointed = "", array = "";
		if(i->isPointed())
			isPointed = "*";
		if(i->getSize() > 0)
			array = "[" + std::to_string(i->getSize()) + "]";	
		std::cout << isPointed << i->getName() << array << ", ";
	}
}
bool VariableDeclaration::isPointedId(std::string const& id)
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
	for(IdentifierDeclarator* idNode : id)
	{
		if(symbole.count(idNode->getName()) == 0)
		{
			Type* tmpType = new PrimitiveType(type);
			if(idNode->isPointed())
			{
				tmpType = new PointerType(*tmpType);
				std::cout << "Pointed variable " << idNode->getName() << std::endl;
			}
			else if(idNode->getSize() > 0)
			{
				tmpType = new PointerType(*tmpType, idNode->getSize());
				std::cout << "Static array " << idNode->getName() << std::endl;
			}
			symbole[idNode->getName()] = tmpType;
		}
		else
		{
			throw std::invalid_argument("Variable " + idNode->getName() + " already exist");
		}
	}
}
