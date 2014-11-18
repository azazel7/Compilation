%{
#include <cstdio>
#include <iostream>
#include <list>
#include <map>

class Type;
std::list<std::map<std::string, Type&> > allSymbole;

extern "C" int yylex();
extern "C" int yyparse();
extern "C" int yylineno;
extern "C" char* yytext;
extern "C" FILE *yyin;

void yyerror(const char *s);

%}

%token <str> IDENTIFIER ICONSTANT FCONSTANT
%token INC_OP DEC_OP LE_OP GE_OP EQ_OP NE_OP
%token INT FLOAT VOID
%token IF ELSE WHILE RETURN FOR
%union {
  char *str;
}
%start program
%%

primary_expression
: IDENTIFIER { std::cout << "primary_expression -> IDENTIFIER" << std::endl;}
| ICONSTANT {std::cout << "primary_expression -> ICONSTANT" << std::endl;}
| FCONSTANT	{std::cout << "primary_expression -> FCONSTANT" << std::endl;}
| '(' expression ')' {std::cout << "primary_expression -> ( expression )" << std::endl;}
| IDENTIFIER '(' ')' {std::cout << "primary_expression -> IDENTIFIER()" << std::endl;}
| IDENTIFIER '(' argument_expression_list ')' {std::cout << "primary_expression -> IDENTIFIER( argument_expression_list )" << std::endl;}
| IDENTIFIER INC_OP {std::cout << "primary_expression -> IDENTIFIER INC_OP" << std::endl;}
| IDENTIFIER DEC_OP {std::cout << "primary_expression -> IDENTIFIER DEC_OP" << std::endl;}
| IDENTIFIER '[' expression ']' {std::cout << "primary_expression -> IDENTIFIER [ expression ]" << std::endl;}
;

argument_expression_list
: expression {std::cout << "argument_expression_list -> expression" << std::endl;}
| argument_expression_list ',' expression {std::cout << "argument_expression_list ->argument_expression_list,  expression" << std::endl;}
;

unary_expression
: primary_expression {std::cout << "unary_expression -> primary_expression" << std::endl;} 
| '-' unary_expression {std::cout << "unary_expression -> - unary_expression" << std::endl;}
| '!' unary_expression {std::cout << "unary_expression -> ! unary_expression" << std::endl;}
;

multiplicative_expression
: unary_expression {std::cout << "multiplicative_expression -> unary_expression" << std::endl;}
| multiplicative_expression '*' unary_expression {std::cout << "multiplicative_expression -> multiplicative_expression * unary_expression" << std::endl;}
;

additive_expression
: multiplicative_expression {std::cout << "additive_expression -> multiplicative_expression" << std::endl;}
| additive_expression '+' multiplicative_expression {std::cout << "additive_expression -> additive_expression + multiplicative_expression" << std::endl;}
| additive_expression '-' multiplicative_expression {std::cout << "additive_expression -> additive_expression - multiplicative_expression" << std::endl;}
;

comparison_expression
: additive_expression {std::cout << "comparison_expression -> additive_expression" << std::endl;}
| additive_expression '<' additive_expression {std::cout << "comparison_expression -> additive_expression < additive_expression" << std::endl;}
| additive_expression '>' additive_expression {std::cout << "comparison_expression -> additive_expression > additive_expression" << std::endl;}
| additive_expression LE_OP additive_expression {std::cout << "comparison_expression -> additive_expression LE_OP additive_expression" << std::endl;}
| additive_expression GE_OP additive_expression {std::cout << "comparison_expression -> additive_expression GE_OP additive_expression" << std::endl;}
| additive_expression EQ_OP additive_expression {std::cout << "comparison_expression -> additive_expression EQ_OP additive_expression" << std::endl;}
| additive_expression NE_OP additive_expression {std::cout << "comparison_expression -> additive_expression NE_OP additive_expression" << std::endl;}
;

expression
: IDENTIFIER '=' comparison_expression {std::cout << "expression -> IDENTIFIER = comparison_expression" << std::endl;}
| IDENTIFIER '[' expression ']' '=' comparison_expression {std::cout << "expression -> IDENTIFIER [expression]" << std::endl;}
| comparison_expression {std::cout << "expression -> comparison_expression " << std::endl;}
;

declaration
: type_name declarator_list ';' {std::cout << "declaration -> type_name declarator_list" << std::endl;}
;

declarator_list
: declarator {std::cout << "declarator_list -> declarator" << std::endl;}
| declarator_list ',' declarator {std::cout << "declarator_list -> declarator_list, declarator" << std::endl;}
;

type_name
: VOID  {std::cout << "type_name -> VOID" << std::endl;}
| INT   {std::cout << "type_name -> INT" << std::endl;}
| FLOAT {std::cout << "type_name -> FLOAT" << std::endl;}
;

declarator
: IDENTIFIER   {std::cout << "declarator -> IDENTIFIER" << std::endl;}
| '*' IDENTIFIER {std::cout << "declarator -> * IDENTIFIER" << std::endl;}
| IDENTIFIER '[' ICONSTANT ']' {std::cout << "declarator -> IDENTIFIER [ ICONSTANT ]" << std::endl;}
| declarator '(' parameter_list ')' {std::cout << "declarator -> declarator (parameter_list )" << std::endl;}
| declarator '(' ')' {std::cout << "declarator -> declarator ()" << std::endl;}
;

parameter_list
: parameter_declaration {std::cout << "parameter_list -> parameter_declaration" << std::endl;}
| parameter_list ',' parameter_declaration {std::cout << "parameter_list -> parameter_list , parameter_declaration" << std::endl;}
;

parameter_declaration
: type_name declarator {std::cout << "parameter_declaration -> type_name declarator" << std::endl;}
;

statement
: compound_statement {std::cout << "statement -> compound_statement" << std::endl;}
| expression_statement  {std::cout << "statement -> expression_statement" << std::endl;}
| selection_statement {std::cout << "statement -> selection_statement" << std::endl;}
| iteration_statement {std::cout << "statement -> iteration_statement" << std::endl;}
| jump_statement {std::cout << "statement -> jump_statement" << std::endl;}
;

compound_statement
: '{' '}' {std::cout << "compound_statement ->  { }" << std::endl;}
| '{' statement_list '}' {std::cout << "compound_statement -> { statement_list }" << std::endl;}
| '{' declaration_list statement_list '}' {std::cout << "compound_statement -> { declaration_list statement_list }" << std::endl;}
;

declaration_list
: declaration {std::cout << "declaration_list -> declaration" << std::endl;}
| declaration_list declaration {std::cout << "declaration_list -> declaration_list declaration" << std::endl;}
;

statement_list
: statement {std::cout << "statement_list -> statement" << std::endl;}
| statement_list statement {std::cout << "statement_list -> statement_list statement" << std::endl;}
;

expression_statement
: ';' {std::cout << "expression_statement -> ;" << std::endl;}
| expression ';' {std::cout << "expression_statement -> expression ;" << std::endl;}
;

selection_statement
: IF '(' expression ')' statement {std::cout << "selection_statement -> IF ( expression ) statement" << std::endl;}
| IF '(' expression ')' statement ELSE statement {std::cout << "selection_statement -> IF ( expression ) statement ELSE statement" << std::endl;}
;

iteration_statement
: WHILE '(' expression ')' statement {std::cout << "iteration_statement -> WHILE ( expression ) statement" << std::endl;}
| FOR '(' expression_statement expression_statement expression ')' statement {std::cout << "iteration_statement -> FOR ( expression_statement expression_statement expression ) statement" << std::endl;}
;

jump_statement
: RETURN ';' {std::cout << "jump_statement -> RETURN ;" << std::endl;}
| RETURN expression ';' {std::cout << "jump_statement -> RETURN expression ;" << std::endl;}
;

program
: external_declaration {std::cout << "program -> external_declaration" << std::endl;}
| program external_declaration {std::cout << "program -> program external_declaration" << std::endl;}
;

external_declaration
: function_definition {std::cout << "external_declaration -> function_definition" << std::endl;}
| declaration {std::cout << "external_declaration -> declaration" << std::endl;}
;

function_definition
: type_name declarator compound_statement {std::cout << "function_definition -> type_name declarator compound_statement" << std::endl;}
;

%%
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int column;

char *file_name = NULL;

void yyerror (const char *s) {
    fflush (stdout);
    fprintf (stderr, "%s:%d:%d: %s\n", file_name, yylineno, column, s);
}


int main (int argc, char *argv[]) {
    FILE *input = NULL;
    if (argc==2) {
	input = fopen (argv[1], "r");
	file_name = strdup (argv[1]);
	if (input) {
	    yyin = input;
	    yyparse();
	}
	else {
	  fprintf (stderr, "%s: Could not open %s\n", *argv, argv[1]);
	    return 1;
	}
	free(file_name);
    }
    else {
	fprintf (stderr, "%s: error: no input file\n", *argv);
	return 1;
    }
    return 0;
}
