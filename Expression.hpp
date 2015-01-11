#pragma once
#include "Node.hpp"

class Expression: public Node
{
	std::string id;
	Node* expressionOffset;
	Node& expression;
	char convertType;
	static const char no_convert;
	static const char convert_to_int;
	static const char convert_to_float;
	public:
		Expression(std::string iden, Node& expr, Node* offset = nullptr);
		void semanticsCheck(void);
		Type const* getType();
		void generateCode(FILE * fd) const;
		void generateFloatingCode(FILE * fd, bool convert = false) const;
		~Expression();
};
