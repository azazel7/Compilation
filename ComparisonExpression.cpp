#include "ComparisonExpression.hpp"
#include "PrimitiveType.hpp"

ComparisonExpression::ComparisonExpression(Node& r, Node &l):Node(ID_COMPARISON), right(r), left(l) 
{
	type = new PrimitiveType(PrimitiveType::int_type);
}
void ComparisonExpression::semanticsCheck(void) const
{
	right.semanticsCheck();
	left.semanticsCheck();
}
Type const* ComparisonExpression::getType()
{
	return type;
};
