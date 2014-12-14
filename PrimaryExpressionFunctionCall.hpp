#ifndef PRIMARY_EXPRESSION_FUNCTION_CALL_HPP
#define PRIMARY_EXPRESSION_FUNCTION_CALL_HPP
#include "Node.hpp"
#include <list>

class PrimaryExpressionFunctionCall : public Node
{
	std::list<Node*> argumentList;
	std::string id;
	public:
		PrimaryExpressionFunctionCall(std::string id, std::list<Node*> argumentList);
		void semanticsCheck(void) const;
		Type const* getType();
		~PrimaryExpressionFunctionCall();
};
#endif
