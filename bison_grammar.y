%{
#include <cstdio>
#include <iostream>
#include <list>
#include <map>
#include "Node.hpp"
#include "Function.hpp"
#include "CompoundStatement.hpp"
#include "VariableDeclaration.hpp"
#include "TypeOperationConversion.hpp"
#include "Expression.hpp"
#include "PrimitiveType.hpp"
#include "ComparisonExpression.hpp"
#include "AdditiveExpression.hpp"
#include "MultiplicativeExpression.hpp"
#include "UnaryExpression.hpp"
#include "PrimaryExpressionIdentifier.hpp"
#include "PrimaryExpressionConstant.hpp"
#include "PrimaryExpressionIdentifierOperation.hpp"
#include "PrimaryExpressionFunctionCall.hpp"
#include "PrimaryExpressionArrayAccess.hpp"
#include "ReturnStatement.hpp"
#include "IfStatement.hpp"
#include "WhileStatement.hpp"
#include "ForStatement.hpp"
#include "PForStatement.hpp"
#include "IdentifierDeclarator.hpp"
#include "ProgramNode.hpp"
#include "ExpressionStatement.hpp"

class Type;
std::list<std::map<std::string, Type&> > allSymbole;
std::list<Node*> stackForTree;


extern "C" int yylex();
extern "C" int yyparse();
extern "C" int yylineno;
extern "C" char* yytext;
extern "C" FILE *yyin;

void yyerror(const char *s);

%}

%token <str> IDENTIFIER ICONSTANT FCONSTANT
%token INC_OP DEC_OP LE_OP GE_OP EQ_OP NE_OP
%token POINTER
%token INT FLOAT VOID
%token IF ELSE WHILE RETURN FOR PFOR
%union {
  char *str;
}
%start program
%%
primary_expression
: IDENTIFIER { std::cerr << "primary_expression -> IDENTIFIER" << std::endl;
		stackForTree.push_front(new PrimaryExpressionIdentifier($1));
		}
| ICONSTANT {std::cerr << "primary_expression -> ICONSTANT" << std::endl;
		stackForTree.push_front(new PrimaryExpressionConstant($1, CONSTANT_INT));
		}
| FCONSTANT	{std::cerr << "primary_expression -> FCONSTANT" << std::endl;
		stackForTree.push_front(new PrimaryExpressionConstant($1, CONSTANT_FLOAT));
		}
| '(' expression ')' {std::cerr << "primary_expression -> ( expression )" << std::endl;
			}
| IDENTIFIER '(' ')' {std::cerr << "primary_expression -> IDENTIFIER()" << std::endl;
		std::list<Node*> argList;
		stackForTree.push_front(new PrimaryExpressionFunctionCall($1, argList));
		}
| IDENTIFIER '(' argument_expression_list ')' {std::cerr << "primary_expression -> IDENTIFIER( argument_expression_list )" << std::endl;
		Node* argTree = stackForTree.front();
		stackForTree.pop_front();
		std::list<Node*> argList = argTree->getChildren();
		if(argList.size() == 0)
			argList.push_front(argTree);
		else
			delete argTree; //argTree is now useless because out of the stack and without children
		Node* functionCall = new PrimaryExpressionFunctionCall($1, argList);
		stackForTree.push_front(functionCall);
		}
| IDENTIFIER INC_OP {std::cerr << "primary_expression -> IDENTIFIER INC_OP" << std::endl;
		stackForTree.push_front(new PrimaryExpressionIdentifierOperation($1, PrimaryExpressionIdentifierOperation::inc));
		}
| IDENTIFIER DEC_OP {std::cerr << "primary_expression -> IDENTIFIER DEC_OP" << std::endl;
		stackForTree.push_front(new PrimaryExpressionIdentifierOperation($1, PrimaryExpressionIdentifierOperation::dec));
		}
| IDENTIFIER '[' expression ']' {std::cerr << "primary_expression -> IDENTIFIER [ expression ]" << std::endl;
		Node* expr = stackForTree.front(); //Take argument_expression_list as child
		stackForTree.pop_front();
		Node* tmp = new PrimaryExpressionArrayAccess($1, *expr); //TODO find something to check that !!!
		stackForTree.push_front(tmp);
		}
;

argument_expression_list
: expression {std::cerr << "argument_expression_list -> expression" << std::endl;}
| argument_expression_list ',' expression {std::cerr << "argument_expression_list ->argument_expression_list,  expression" << std::endl;
		Node* expression = stackForTree.front();
		stackForTree.pop_front();
		Node* argList = stackForTree.front();
		stackForTree.pop_front();
		if(argList->getId() != ID_ARGUMENT_EXPRESSION_LIST)
		{
			Node* tmp = new Node(ID_ARGUMENT_EXPRESSION_LIST);
			tmp->addChild(*argList);
			argList = tmp;
		}
		argList->addChild(*expression);
		stackForTree.push_front(argList);
		}
;

unary_expression
: primary_expression {std::cerr << "unary_expression -> primary_expression" << std::endl;} 
| '-' unary_expression {std::cerr << "unary_expression -> - unary_expression" << std::endl;
		Node* right = stackForTree.front(); 
		stackForTree.pop_front();
		Node* tmp = new UnaryExpression(*right);
		stackForTree.push_front(tmp);
		}
| '!' unary_expression {std::cerr << "unary_expression -> ! unary_expression" << std::endl;
		Node* right = stackForTree.front(); 
		stackForTree.pop_front();
		Node* tmp = new UnaryExpression(*right);
		stackForTree.push_front(tmp);
		}
;

multiplicative_expression
: unary_expression {std::cerr << "multiplicative_expression -> unary_expression" << std::endl;}
| multiplicative_expression '*' unary_expression {std::cerr << "multiplicative_expression -> multiplicative_expression * unary_expression" << std::endl;
		Node* left = stackForTree.front(); 
		stackForTree.pop_front();
		Node* right = stackForTree.front(); 
		stackForTree.pop_front();
		Node* tmp = new MultiplicativeExpression(*right, *left); 
		stackForTree.push_front(tmp);
		}
;

additive_expression
: multiplicative_expression {std::cerr << "additive_expression -> multiplicative_expression" << std::endl;}
| additive_expression '+' multiplicative_expression {std::cerr << "additive_expression -> additive_expression + multiplicative_expression" << std::endl;
		Node* left = stackForTree.front(); 
		stackForTree.pop_front();
		Node* right = stackForTree.front(); 
		stackForTree.pop_front();
		Node* tmp = new AdditiveExpression(*right, *left, AdditiveExpression::add); 
		stackForTree.push_front(tmp);
		}
| additive_expression '-' multiplicative_expression {std::cerr << "additive_expression -> additive_expression - multiplicative_expression" << std::endl;
		Node* left = stackForTree.front(); 
		stackForTree.pop_front();
		Node* right = stackForTree.front(); 
		stackForTree.pop_front();
		Node* tmp = new AdditiveExpression(*right, *left, AdditiveExpression::sub); 
		stackForTree.push_front(tmp);
		}
;

comparison_expression
: additive_expression {std::cerr << "comparison_expression -> additive_expression" << std::endl;}
| additive_expression '<' additive_expression {std::cerr << "comparison_expression -> additive_expression < additive_expression" << std::endl;
		Node* left = stackForTree.front(); 
		stackForTree.pop_front();
		Node* right = stackForTree.front(); 
		stackForTree.pop_front();
		Node* tmp = new ComparisonExpression(*right, *left, ComparisonExpression::L); 
		stackForTree.push_front(tmp);
		}
| additive_expression '>' additive_expression {std::cerr << "comparison_expression -> additive_expression > additive_expression" << std::endl;
		Node* left = stackForTree.front(); 
		stackForTree.pop_front();
		Node* right = stackForTree.front(); 
		stackForTree.pop_front();
		Node* tmp = new ComparisonExpression(*right, *left, ComparisonExpression::G); 
		stackForTree.push_front(tmp);
		}
| additive_expression LE_OP additive_expression {std::cerr << "comparison_expression -> additive_expression LE_OP additive_expression" << std::endl;
		Node* left = stackForTree.front(); 
		stackForTree.pop_front();
		Node* right = stackForTree.front(); 
		stackForTree.pop_front();
		Node* tmp = new ComparisonExpression(*right, *left, ComparisonExpression::LE); 
		stackForTree.push_front(tmp);
		}
| additive_expression GE_OP additive_expression {std::cerr << "comparison_expression -> additive_expression GE_OP additive_expression" << std::endl;
		Node* left = stackForTree.front(); 
		stackForTree.pop_front();
		Node* right = stackForTree.front(); 
		stackForTree.pop_front();
		Node* tmp = new ComparisonExpression(*right, *left, ComparisonExpression::GE); 
		stackForTree.push_front(tmp);
		}
| additive_expression EQ_OP additive_expression {std::cerr << "comparison_expression -> additive_expression EQ_OP additive_expression" << std::endl;
		Node* left = stackForTree.front(); 
		stackForTree.pop_front();
		Node* right = stackForTree.front(); 
		stackForTree.pop_front();
		Node* tmp = new ComparisonExpression(*right, *left, ComparisonExpression::EQ); 
		stackForTree.push_front(tmp);
		}
| additive_expression NE_OP additive_expression {std::cerr << "comparison_expression -> additive_expression NE_OP additive_expression" << std::endl;
		Node* left = stackForTree.front(); 
		stackForTree.pop_front();
		Node* right = stackForTree.front(); 
		stackForTree.pop_front();
		Node* tmp = new ComparisonExpression(*right, *left, ComparisonExpression::NE); 
		stackForTree.push_front(tmp);
		}
;

expression
: IDENTIFIER '=' comparison_expression {std::cerr << "expression -> IDENTIFIER = comparison_expression" << std::endl;
		Node* tmp = new Expression($1, *stackForTree.front());
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
| IDENTIFIER '[' expression ']' '=' comparison_expression {std::cerr << "expression -> IDENTIFIER [expression] = comparison_expression" << std::endl;
		Node* comparisonExpression = stackForTree.front();
		stackForTree.pop_front();
		Node* expression = stackForTree.front();
		stackForTree.pop_front();
		Node* tmp = new Expression($1, *comparisonExpression, expression);
		stackForTree.push_front(tmp);
		}
| comparison_expression {std::cerr << "expression -> comparison_expression " << std::endl;
	}
;

declaration
: type_name declarator_list ';' {std::cerr << "declaration -> type_name declarator_list" << std::endl;
		Node* identifier = stackForTree.front();
		stackForTree.pop_front();
		Node* type = stackForTree.front();
		stackForTree.pop_front();
		Node* tmp = new VariableDeclaration(type, identifier);
		stackForTree.push_front(tmp);
		}
;

declarator_list
: declarator {std::cerr << "declarator_list -> declarator" << std::endl;
		Node* tmp = new Node(ID_STATEMENT_LIST);
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
| declarator_list ',' declarator {std::cerr << "declarator_list -> declarator_list, declarator" << std::endl;
		Node* tmp = new Node(ID_STATEMENT_LIST);
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		tmp->addChild(*(new Node(",")));
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
;

type_name
: VOID  {std::cerr << "type_name -> VOID " << std::endl; 
		stackForTree.push_front(new Node(PrimitiveType::void_type, ID_TYPE));
	}
| INT   {std::cerr << "type_name -> INT" << std::endl;
		stackForTree.push_front(new Node(PrimitiveType::int_type, ID_TYPE));
	}
| FLOAT {std::cerr << "type_name -> FLOAT" << std::endl;
		stackForTree.push_front(new Node(PrimitiveType::float_type, ID_TYPE));
	}
;

declarator
: IDENTIFIER   {std::cerr << "declarator -> IDENTIFIER" << std::endl;
		stackForTree.push_front(new IdentifierDeclarator($1));
		}
| '*' IDENTIFIER {std::cerr << "declarator -> * IDENTIFIER" << std::endl;//Be careful, usually, the star is before IDENTIFIER 
		stackForTree.push_front(new IdentifierDeclarator($2, true));
		}
| IDENTIFIER '[' ICONSTANT ']' {std::cerr << "declarator -> IDENTIFIER(" << $1 << ") [ ICONSTANT (" << atoi($3) << ") ]" << std::endl;
		stackForTree.push_front(new IdentifierDeclarator($1, atoi($3))); 
		}
| declarator '(' parameter_list ')' {std::cerr << "declarator -> declarator (parameter_list )" << std::endl;
		Node* parameterList = stackForTree.front(); //Take decarator as child
		stackForTree.pop_front();
		Node* tmp = stackForTree.front(); //Take parameter_list as child
		stackForTree.pop_front();
		tmp->setId(ID_DECLARATOR);
		tmp->addChild(*parameterList);
		stackForTree.push_front(tmp); //Put this declarator without value
		}
| declarator '(' ')' {std::cerr << "declarator -> declarator ()" << std::endl;
		stackForTree.front()->setId(ID_DECLARATOR);
		}
;

parameter_list
: parameter_declaration {std::cerr << "parameter_list -> parameter_declaration" << std::endl;}
| parameter_list ',' parameter_declaration {std::cerr << "parameter_list -> parameter_list , parameter_declaration" << std::endl;
		Node* tmp = new Node();
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		tmp->addChild(*(new Node(",")));
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
;

parameter_declaration
: type_name declarator {std::cerr << "parameter_declaration -> type_name declarator" << std::endl;
		Node* id = stackForTree.front();
		stackForTree.pop_front();
		Node* type = stackForTree.front();
		stackForTree.pop_front();
		Node* tmp = new VariableDeclaration(type, id);
		tmp->setId(ID_PARAMETER);
		stackForTree.push_front(tmp);
		}
;

statement
: compound_statement {std::cerr << "statement -> compound_statement" << std::endl;
		//Add an inter node because we want an additional layer for compound_statement
		/*Node* tmp = new Node(ID_STATEMENT);*/
		/*tmp->addChild(*stackForTree.front());*/
		/*stackForTree.pop_front();*/
		/*stackForTree.push_front(tmp);*/
		}
| expression_statement  {std::cerr << "statement -> expression_statement" << std::endl;
		stackForTree.front()->setId(ID_STATEMENT);
		}
| selection_statement {std::cerr << "statement -> selection_statement" << std::endl;
		stackForTree.front()->setId(ID_STATEMENT);
		}
| iteration_statement {std::cerr << "statement -> iteration_statement" << std::endl;
		stackForTree.front()->setId(ID_STATEMENT);
		}
| jump_statement {std::cerr << "statement -> jump_statement" << std::endl;
		stackForTree.front()->setId(ID_STATEMENT);
		}
;

compound_statement
: '{' '}' {std::cerr << "compound_statement ->  { }" << std::endl;
		Node* tmp = new CompoundStatement("{ }", ID_STATEMENT);//Even if this node is useless, we have to let it here, else the stackForTree will be empty for the next rule using compound_statement
		stackForTree.push_front(tmp);
		}
| '{' statement_list '}' {std::cerr << "compound_statement -> { statement_list }" << std::endl;
		Node* statement = stackForTree.front();
		stackForTree.pop_front();
		Node* tmp = new CompoundStatement(statement);
		//From here, we can't be sure if statement has been freed, but CompoundStatement will manage itself everything about it
		stackForTree.push_front(tmp);
		}
| '{' declaration_list statement_list '}' {std::cerr << "compound_statement -> { declaration_list statement_list }" << std::endl;
		Node* statement = stackForTree.front();
		stackForTree.pop_front();
		Node* declaration = stackForTree.front();
		stackForTree.pop_front();
		Node* tmp = new CompoundStatement(statement, declaration);
		//From here, we can't be sure if statement and declaration have been freed, but CompoundStatement will manage itself everything about it
		stackForTree.push_front(tmp);
		}
;

declaration_list
: declaration {std::cerr << "declaration_list -> declaration" << std::endl;}
| declaration_list declaration {std::cerr << "declaration_list -> declaration_list declaration" << std::endl;
		Node* tmp = new Node();
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
;

statement_list
: statement {std::cerr << "statement_list -> statement" << std::endl;}
| statement_list statement {std::cerr << "statement_list -> statement_list statement" << std::endl;
		Node* tmp = new Node(ID_STATEMENT_LIST);
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
;

expression_statement
: ';' {std::cerr << "expression_statement -> ;" << std::endl;
		Node* tmp = new Node();
		stackForTree.push_front(tmp);
}
| expression ';' {std::cerr << "expression_statement -> expression ;" << std::endl;
		Node* expression = stackForTree.front();
		stackForTree.pop_front();
		Node* tmp = new ExpressionStatement(*expression);
		stackForTree.push_front(tmp);
		}
;

selection_statement
: IF '(' expression ')' statement {std::cerr << "selection_statement -> IF ( expression ) statement" << std::endl;
		Node* statement = stackForTree.front();
		stackForTree.pop_front();
		Node* expression = stackForTree.front();
		stackForTree.pop_front();
		Node* ifStatement = new IfStatement(*expression, *statement);
		stackForTree.push_front(ifStatement);
		}
| IF '(' expression ')' statement ELSE statement {std::cerr << "selection_statement -> IF ( expression ) statement ELSE statement" << std::endl;
		Node* elseStatement = stackForTree.front();
		stackForTree.pop_front();
		Node* statement = stackForTree.front();
		stackForTree.pop_front();
		Node* expression = stackForTree.front();
		stackForTree.pop_front();
		Node* ifStatement = new IfStatement(*expression, *statement, elseStatement);
		stackForTree.push_front(ifStatement);
		}
;

iteration_statement
: WHILE '(' expression ')' statement {std::cerr << "iteration_statement -> WHILE ( expression ) statement" << std::endl;
		Node* statement = stackForTree.front();
		stackForTree.pop_front();
		Node* expression = stackForTree.front();
		stackForTree.pop_front();
		Node* ifStatement = new IfStatement(*expression, *statement);
		stackForTree.push_front(ifStatement);
		}
| FOR '(' expression_statement expression_statement expression ')' statement {std::cerr << "iteration_statement -> FOR ( expression_statement expression_statement expression ) statement" << std::endl;
		Node* statement = stackForTree.front();
		stackForTree.pop_front();
		Node* exprVar = stackForTree.front();
		stackForTree.pop_front();
		Node* exprCond = stackForTree.front();
		stackForTree.pop_front();
		Node* exprInit = stackForTree.front();
		stackForTree.pop_front();
		Node* forStatement = new ForStatement(*exprInit, *exprCond, *exprVar, *statement);
		stackForTree.push_front(forStatement);
		}
| PFOR '(' IDENTIFIER '=' expression ';' IDENTIFIER '<' expression ';' IDENTIFIER INC_OP ')' statement {std::cerr << "iteration_statement -> PFOR ( expression_statement expression_statement expression ) statement" << std::endl;
		Node* statement = stackForTree.front();
		stackForTree.pop_front();
		Node* exprCond = stackForTree.front();
		stackForTree.pop_front();
		Node* exprInit = stackForTree.front();
		stackForTree.pop_front();
		Node* pForStatement = new PForStatement($3, *exprInit, $7, *exprCond, $11, *statement);
		stackForTree.push_front(pForStatement);
		}
;

jump_statement
: RETURN ';' {std::cerr << "jump_statement -> RETURN ;" << std::endl;
		Node* tmp = new ReturnStatement();
		stackForTree.push_front(tmp);
		}
| RETURN expression ';' {std::cerr << "jump_statement -> RETURN expression ;" << std::endl;
		Node* tmp = new ReturnStatement(stackForTree.front());
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
;

program : external_declaration {std::cerr << "program -> external_declaration" << std::endl;}
| program external_declaration {std::cerr << "program -> program external_declaration" << std::endl;
		Node* external_declaration = stackForTree.front();
		stackForTree.pop_front();
		Node* program = stackForTree.front();
		stackForTree.pop_front();
		if(program->getId() != ID_PROGRAM)
		{
			Node* tmp = new ProgramNode();
			tmp->addChild(*program);
			program = tmp;
		}
		program->addChild(*external_declaration);
		stackForTree.push_front(program);
		}
;

external_declaration
: function_definition {std::cerr << "external_declaration -> function_definition" << std::endl;}
| declaration {std::cerr << "external_declaration -> declaration" << std::endl;
		stackForTree.front()->setId(ID_GLOBAL_DECLARATOR);
		}
;

function_definition
: type_name declarator compound_statement {std::cerr << "function_definition -> type_name declarator compound_statement" << std::endl;
		Node* body = stackForTree.front();
		stackForTree.pop_front();
		Node* argument = stackForTree.front();
		stackForTree.pop_front();
		Node * type = stackForTree.front(); 
		stackForTree.pop_front(); 
		Node* tmp = new Function(type, argument, body);
		stackForTree.push_front(tmp);
		}
;

%%
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int column;

char *file_name = NULL;

void yyerror (const char *s)
{
	fflush (stdout);
	fprintf (stderr, "%s:%d:%d: %s\n", file_name, yylineno, column, s);
}

void replace_extension(std::string& str, std::string const extension)
{
	while(str[str.size() - 1] != '.')
		str.pop_back();
	str = str + extension;
}

int main (int argc, char *argv[])
{
	FILE *input = NULL;
	FILE *output = NULL;
	TypeOperationConversion::initTable();
	if (argc==2)
	{
		input = fopen (argv[1], "r");
		std::string filenameOutput = argv[1];
		replace_extension(filenameOutput, "s");
		output = fopen (filenameOutput.c_str(), "w");
		file_name = strdup (argv[1]);
		
		if (input)
		{
			yyin = input;
			yyparse();
			stackForTree.front()->flattenFunction();
			stackForTree.front()->createSymboleTable();
			stackForTree.front()->printSymboleTable();
			stackForTree.front()->semanticsCheck();
			stackForTree.front()->generateCode(output);
			/*stackForTree.front()->print();*/
			fclose(input);
			fclose(output);
			delete stackForTree.front();
		}
		else
		{
			fprintf (stderr, "%s: Could not open %s\n", *argv, argv[1]);
			return 1;
		}
		free(file_name);
	}
	else
	{
		fprintf (stderr, "%s: error: no input file\n", *argv);
		return 1;
	}
	return 0;
}
//Les types: les types de base sont void, int et float. DONE
//Les types construits sont les tableaux et les fonctions. DONE
//Les tableaux ne peuvent être que des tableaux à une dimension, de taille quelconque. DONE
//Les tableaux peuvent être alloués statiquement ou dynamiquement.
//Ils peuvent être déclarés soit comme des pointeurs soit comme des tableaux (alloués statiquement dans ce cas). DONE
//Les fonctions: les fonctions sont toutes globales et on ne peut pas déclarer de fonction dans des fonctions. DONE
//Les paramètres: Dans une définition de fonction, les paramètres peuvent être des tableaux, des entiers ou des flottants.PROBABLY DONE
//Il est possible de déclarer des fonctions sans les définir. Cela permet de déclarer et d'appeler des fonctions qui seront définies par des bibliothèques externes. On veuillera à respecter le protocole d'appel afin de permettre cette fonctionnalité.
//Les fonctions "printint(int)" et "printfloat(float)" seront connues par l'utilisateur et pourront être utilisées sans déclaration dans un programme. DONE
//Les operations: les règles de typage sont celles du C. DONE
//Par ailleurs, on interdira les calculs sur les pointeurs.
//L'affectation: comme en C. Dans une affectation, un pointeur peut prendre la valeur soit d'un autre pointeur, soit d'un tableau défini statiquement. DONE
//Un tableau statique (déclaré avec t[cste]) ne pourra être à gauche de l'affectation. DONE
//Les boucles: les boucles for et while se comportent comme les boucles C DONE
//Un bloc d'instructions: comme en C DONE
//Le if: la conditionnelle if pourra avoir ou non une partie else. DONE
