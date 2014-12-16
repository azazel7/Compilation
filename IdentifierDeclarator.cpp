#include "IdentifierDeclarator.hpp"


IdentifierDeclarator::IdentifierDeclarator(std::string name, bool pointed): Node(name, ID_DECLARATOR), pointed(pointed)
{
}
IdentifierDeclarator::IdentifierDeclarator(std::string name, int size): Node(name, ID_DECLARATOR), size(size)
{
}
bool IdentifierDeclarator::isPointed(void) const
{
	return pointed;
}
int IdentifierDeclarator::getSize(void) const
{
	return this->size;
}
