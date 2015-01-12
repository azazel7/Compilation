%{
#include <cstdio>
#include <iostream>
#include <list>
#include <map>
#include <exception>
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
: IDENTIFIER { 
		stackForTree.push_front(new PrimaryExpressionIdentifier($1));
		}
| ICONSTANT {
		stackForTree.push_front(new PrimaryExpressionConstant($1, CONSTANT_INT));
		}
| FCONSTANT	{
		stackForTree.push_front(new PrimaryExpressionConstant($1, CONSTANT_FLOAT));
		}
| '(' expression ')' {
			}
| IDENTIFIER '(' ')' {
		std::list<Node*> argList;
		stackForTree.push_front(new PrimaryExpressionFunctionCall($1, argList));
		}
| IDENTIFIER '(' argument_expression_list ')' {
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
| IDENTIFIER INC_OP {
		stackForTree.push_front(new PrimaryExpressionIdentifierOperation($1, PrimaryExpressionIdentifierOperation::inc));
		}
| IDENTIFIER DEC_OP {
		stackForTree.push_front(new PrimaryExpressionIdentifierOperation($1, PrimaryExpressionIdentifierOperation::dec));
		}
| IDENTIFIER '[' expression ']' {
		Node* expr = stackForTree.front(); //Take argument_expression_list as child
		stackForTree.pop_front();
		Node* tmp = new PrimaryExpressionArrayAccess($1, *expr); //TODO find something to check that !!!
		stackForTree.push_front(tmp);
		}
;

argument_expression_list
: expression {}
| argument_expression_list ',' expression {
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
: primary_expression {} 
| '-' unary_expression {
		Node* right = stackForTree.front(); 
		stackForTree.pop_front();
		Node* tmp = new UnaryExpression(*right);
		stackForTree.push_front(tmp);
		}
| '!' unary_expression {
		Node* right = stackForTree.front(); 
		stackForTree.pop_front();
		Node* tmp = new UnaryExpression(*right);
		stackForTree.push_front(tmp);
		}
;

multiplicative_expression
: unary_expression {}
| multiplicative_expression '*' unary_expression {
		Node* left = stackForTree.front(); 
		stackForTree.pop_front();
		Node* right = stackForTree.front(); 
		stackForTree.pop_front();
		Node* tmp = new MultiplicativeExpression(*right, *left); 
		stackForTree.push_front(tmp);
		}
;

additive_expression
: multiplicative_expression {}
| additive_expression '+' multiplicative_expression {
		Node* left = stackForTree.front(); 
		stackForTree.pop_front();
		Node* right = stackForTree.front(); 
		stackForTree.pop_front();
		Node* tmp = new AdditiveExpression(*right, *left, AdditiveExpression::add); 
		stackForTree.push_front(tmp);
		}
| additive_expression '-' multiplicative_expression {
		Node* left = stackForTree.front(); 
		stackForTree.pop_front();
		Node* right = stackForTree.front(); 
		stackForTree.pop_front();
		Node* tmp = new AdditiveExpression(*right, *left, AdditiveExpression::sub); 
		stackForTree.push_front(tmp);
		}
;

comparison_expression
: additive_expression {}
| additive_expression '<' additive_expression {
		Node* left = stackForTree.front(); 
		stackForTree.pop_front();
		Node* right = stackForTree.front(); 
		stackForTree.pop_front();
		Node* tmp = new ComparisonExpression(*right, *left, ComparisonExpression::L); 
		stackForTree.push_front(tmp);
		}
| additive_expression '>' additive_expression {
		Node* left = stackForTree.front(); 
		stackForTree.pop_front();
		Node* right = stackForTree.front(); 
		stackForTree.pop_front();
		Node* tmp = new ComparisonExpression(*right, *left, ComparisonExpression::G); 
		stackForTree.push_front(tmp);
		}
| additive_expression LE_OP additive_expression {
		Node* left = stackForTree.front(); 
		stackForTree.pop_front();
		Node* right = stackForTree.front(); 
		stackForTree.pop_front();
		Node* tmp = new ComparisonExpression(*right, *left, ComparisonExpression::LE); 
		stackForTree.push_front(tmp);
		}
| additive_expression GE_OP additive_expression {
		Node* left = stackForTree.front(); 
		stackForTree.pop_front();
		Node* right = stackForTree.front(); 
		stackForTree.pop_front();
		Node* tmp = new ComparisonExpression(*right, *left, ComparisonExpression::GE); 
		stackForTree.push_front(tmp);
		}
| additive_expression EQ_OP additive_expression {
		Node* left = stackForTree.front(); 
		stackForTree.pop_front();
		Node* right = stackForTree.front(); 
		stackForTree.pop_front();
		Node* tmp = new ComparisonExpression(*right, *left, ComparisonExpression::EQ); 
		stackForTree.push_front(tmp);
		}
| additive_expression NE_OP additive_expression {
		Node* left = stackForTree.front(); 
		stackForTree.pop_front();
		Node* right = stackForTree.front(); 
		stackForTree.pop_front();
		Node* tmp = new ComparisonExpression(*right, *left, ComparisonExpression::NE); 
		stackForTree.push_front(tmp);
		}
;

expression
: IDENTIFIER '=' comparison_expression {
		Node* tmp = new Expression($1, *stackForTree.front());
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
| IDENTIFIER '[' expression ']' '=' comparison_expression {
		Node* comparisonExpression = stackForTree.front();
		stackForTree.pop_front();
		Node* expression = stackForTree.front();
		stackForTree.pop_front();
		Node* tmp = new Expression($1, *comparisonExpression, expression);
		stackForTree.push_front(tmp);
		}
| comparison_expression {
	}
;

declaration
: type_name declarator_list ';' {
		Node* identifier = stackForTree.front();
		stackForTree.pop_front();
		Node* type = stackForTree.front();
		stackForTree.pop_front();
		Node* tmp = new VariableDeclaration(type, identifier);
		stackForTree.push_front(tmp);
		}
;

declarator_list
: declarator {
		Node* tmp = new Node(ID_STATEMENT_LIST);
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
| declarator_list ',' declarator {
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
: VOID  {
		stackForTree.push_front(new Node(PrimitiveType::void_type, ID_TYPE));
	}
| INT   {
		stackForTree.push_front(new Node(PrimitiveType::int_type, ID_TYPE));
	}
| FLOAT {
		stackForTree.push_front(new Node(PrimitiveType::float_type, ID_TYPE));
	}
;

declarator
: IDENTIFIER   {
		stackForTree.push_front(new IdentifierDeclarator($1));
		}
| '*' IDENTIFIER {
		stackForTree.push_front(new IdentifierDeclarator($2, true));
		}
| IDENTIFIER '[' ICONSTANT ']' {
		stackForTree.push_front(new IdentifierDeclarator($1, atoi($3))); 
		}
| declarator '(' parameter_list ')' {
		Node* parameterList = stackForTree.front(); //Take decarator as child
		stackForTree.pop_front();
		Node* tmp = stackForTree.front(); //Take parameter_list as child
		stackForTree.pop_front();
		tmp->setId(ID_DECLARATOR);
		tmp->addChild(*parameterList);
		stackForTree.push_front(tmp); //Put this declarator without value
		}
| declarator '(' ')' {
		stackForTree.front()->setId(ID_DECLARATOR);
		}
;

parameter_list
: parameter_declaration {}
| parameter_list ',' parameter_declaration {
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
: type_name declarator {
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
: compound_statement {}
| expression_statement  {
		stackForTree.front()->setId(ID_STATEMENT);
		}
| selection_statement {
		stackForTree.front()->setId(ID_STATEMENT);
		}
| iteration_statement {
		stackForTree.front()->setId(ID_STATEMENT);
		}
| jump_statement {
		stackForTree.front()->setId(ID_STATEMENT);
		}
;

compound_statement
: '{' '}' {
		Node* tmp = new CompoundStatement("{ }", ID_STATEMENT);//Even if this node is useless, we have to let it here, else the stackForTree will be empty for the next rule using compound_statement
		stackForTree.push_front(tmp);
		}
| '{' statement_list '}' {
		Node* statement = stackForTree.front();
		stackForTree.pop_front();
		Node* tmp = new CompoundStatement(statement);
		//From here, we can't be sure if statement has been freed, but CompoundStatement will manage itself everything about it
		stackForTree.push_front(tmp);
		}
| '{' declaration_list statement_list '}' {
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
: declaration {}
| declaration_list declaration {
		Node* tmp = new Node();
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
;

statement_list
: statement {}
| statement_list statement {
		Node* tmp = new Node(ID_STATEMENT_LIST);
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
;

expression_statement
: ';' {
		Node* tmp = new Node();
		stackForTree.push_front(tmp);
}
| expression ';' {
		Node* expression = stackForTree.front();
		stackForTree.pop_front();
		Node* tmp = new ExpressionStatement(*expression);
		stackForTree.push_front(tmp);
		}
;

selection_statement
: IF '(' expression ')' statement {
		Node* statement = stackForTree.front();
		stackForTree.pop_front();
		Node* expression = stackForTree.front();
		stackForTree.pop_front();
		Node* ifStatement = new IfStatement(*expression, *statement);
		stackForTree.push_front(ifStatement);
		}
| IF '(' expression ')' statement ELSE statement {
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
: WHILE '(' expression ')' statement {
		Node* statement = stackForTree.front();
		stackForTree.pop_front();
		Node* expression = stackForTree.front();
		stackForTree.pop_front();
		Node* ifStatement = new IfStatement(*expression, *statement);
		stackForTree.push_front(ifStatement);
		}
| FOR '(' expression_statement expression_statement expression ')' statement {
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
| PFOR '(' IDENTIFIER '=' expression ';' IDENTIFIER '<' expression ';' IDENTIFIER INC_OP ')' statement {
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
: RETURN ';' {
		Node* tmp = new ReturnStatement();
		stackForTree.push_front(tmp);
		}
| RETURN expression ';' {
		Node* tmp = new ReturnStatement(stackForTree.front());
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
;

program : external_declaration {
		Node* program = stackForTree.front();
		stackForTree.pop_front();
		Node* tmp = new ProgramNode();
		tmp->addChild(*program);
		stackForTree.push_front(tmp);
		}
| program external_declaration {
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
: function_definition {}
| declaration {
		stackForTree.front()->setId(ID_GLOBAL_DECLARATOR);
		}
;

function_definition
: type_name declarator compound_statement {
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
	exit(0);
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
			try
			{
				stackForTree.front()->flattenFunction();
				stackForTree.front()->createSymboleTable();
				stackForTree.front()->semanticsCheck();
				stackForTree.front()->generateCode(output);
			}
			catch(std::exception &e)
			{
				std::cerr << "Error " << e.what() << std::endl;
			}
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
//Les tableaux peuvent être alloués statiquement ou dynamiquement. DONE
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
