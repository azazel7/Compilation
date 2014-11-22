%{
#include <cstdio>
#include <iostream>
#include <list>
#include <map>
#include "Node.hpp"
#include "Function.hpp"

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
%token INT FLOAT VOID
%token IF ELSE WHILE RETURN FOR
%union {
  char *str;
}
%start program
%%

primary_expression
: IDENTIFIER { std::cout << "primary_expression -> IDENTIFIER" << std::endl;
		stackForTree.push_front(new Node($1));
		}
| ICONSTANT {std::cout << "primary_expression -> ICONSTANT" << std::endl;
		stackForTree.push_front(new Node($1));
		}
| FCONSTANT	{std::cout << "primary_expression -> FCONSTANT" << std::endl;
		stackForTree.push_front(new Node($1));
		}
| '(' expression ')' {std::cout << "primary_expression -> ( expression )" << std::endl;
		Node* tmp = new Node();
		tmp->addChild(*(new Node("(")));
		tmp->addChild(*stackForTree.front()); //Take argument_expression_list as child
		stackForTree.pop_front();
		tmp->addChild(*(new Node(")")));
		stackForTree.push_front(tmp);
		}
| IDENTIFIER '(' ')' {std::cout << "primary_expression -> IDENTIFIER()" << std::endl;
		stackForTree.push_front(new Node(std::string($1) + "()"));
		}
| IDENTIFIER '(' argument_expression_list ')' {std::cout << "primary_expression -> IDENTIFIER( argument_expression_list )" << std::endl;
		Node* tmp = new Node($1);
		tmp->addChild(*(new Node(")")));
		tmp->addChild(*stackForTree.front()); //Take argument_expression_list as child
		stackForTree.pop_front();
		tmp->addChild(*(new Node("(")));
		stackForTree.push_front(tmp);
		}
| IDENTIFIER INC_OP {std::cout << "primary_expression -> IDENTIFIER INC_OP" << std::endl;
		stackForTree.push_front(new Node(std::string($1) + "++"));
		}
| IDENTIFIER DEC_OP {std::cout << "primary_expression -> IDENTIFIER DEC_OP" << std::endl;
		stackForTree.push_front(new Node(std::string($1) + "--"));
		}
| IDENTIFIER '[' expression ']' {std::cout << "primary_expression -> IDENTIFIER [ expression ]" << std::endl;
		Node* tmp = new Node($1);
		tmp->addChild(*(new Node("[")));
		tmp->addChild(*stackForTree.front()); //Take argument_expression_list as child
		stackForTree.pop_front();
		tmp->addChild(*(new Node("]")));
		stackForTree.push_front(tmp);
		}
;

argument_expression_list
: expression {std::cout << "argument_expression_list -> expression" << std::endl;}
| argument_expression_list ',' expression {std::cout << "argument_expression_list ->argument_expression_list,  expression" << std::endl;
		Node* tmp = new Node();
		tmp->addChild(*stackForTree.front()); //Take unary_expression as child
		stackForTree.pop_front();
		tmp->addChild(*(new Node(",")));
		tmp->addChild(*stackForTree.front()); //Take unary_expression as child
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
;

unary_expression
: primary_expression {std::cout << "unary_expression -> primary_expression" << std::endl;} 
| '-' unary_expression {std::cout << "unary_expression -> - unary_expression" << std::endl;
		Node* tmp = new Node("-");
		tmp->addChild(*stackForTree.front()); //Take unary_expression as child
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
| '!' unary_expression {std::cout << "unary_expression -> ! unary_expression" << std::endl;
		Node* tmp = new Node("!");
		tmp->addChild(*stackForTree.front()); //Take unary_expression as child
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
;

multiplicative_expression
: unary_expression {std::cout << "multiplicative_expression -> unary_expression" << std::endl;}
| multiplicative_expression '*' unary_expression {std::cout << "multiplicative_expression -> multiplicative_expression * unary_expression" << std::endl;
		Node* tmp = new Node();
		tmp->addChild(*stackForTree.front()); 
		stackForTree.pop_front();
		tmp->addChild(*(new Node("*")));
		tmp->addChild(*stackForTree.front()); 
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
;

additive_expression
: multiplicative_expression {std::cout << "additive_expression -> multiplicative_expression" << std::endl;}
| additive_expression '+' multiplicative_expression {std::cout << "additive_expression -> additive_expression + multiplicative_expression" << std::endl;
		Node* tmp = new Node();
		tmp->addChild(*stackForTree.front()); 
		stackForTree.pop_front();
		tmp->addChild(*(new Node("+")));
		tmp->addChild(*stackForTree.front()); 
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
| additive_expression '-' multiplicative_expression {std::cout << "additive_expression -> additive_expression - multiplicative_expression" << std::endl;
		Node* tmp = new Node();
		tmp->addChild(*stackForTree.front()); 
		stackForTree.pop_front();
		tmp->addChild(*(new Node("-")));
		tmp->addChild(*stackForTree.front()); 
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
;

comparison_expression
: additive_expression {std::cout << "comparison_expression -> additive_expression" << std::endl;}
| additive_expression '<' additive_expression {std::cout << "comparison_expression -> additive_expression < additive_expression" << std::endl;
		Node* tmp = new Node();
		tmp->addChild(*stackForTree.front()); 
		stackForTree.pop_front();
		tmp->addChild(*(new Node("<")));
		tmp->addChild(*stackForTree.front()); 
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
| additive_expression '>' additive_expression {std::cout << "comparison_expression -> additive_expression > additive_expression" << std::endl;
		Node* tmp = new Node();
		tmp->addChild(*stackForTree.front()); 
		stackForTree.pop_front();
		tmp->addChild(*(new Node(">")));
		tmp->addChild(*stackForTree.front()); 
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
| additive_expression LE_OP additive_expression {std::cout << "comparison_expression -> additive_expression LE_OP additive_expression" << std::endl;
		Node* tmp = new Node();
		tmp->addChild(*stackForTree.front()); 
		stackForTree.pop_front();
		tmp->addChild(*(new Node("<=")));
		tmp->addChild(*stackForTree.front()); 
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
| additive_expression GE_OP additive_expression {std::cout << "comparison_expression -> additive_expression GE_OP additive_expression" << std::endl;
		Node* tmp = new Node();
		tmp->addChild(*stackForTree.front()); 
		stackForTree.pop_front();
		tmp->addChild(*(new Node(">=")));
		tmp->addChild(*stackForTree.front()); 
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
| additive_expression EQ_OP additive_expression {std::cout << "comparison_expression -> additive_expression EQ_OP additive_expression" << std::endl;
		Node* tmp = new Node();
		tmp->addChild(*stackForTree.front()); 
		stackForTree.pop_front();
		tmp->addChild(*(new Node("==")));
		tmp->addChild(*stackForTree.front()); 
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
| additive_expression NE_OP additive_expression {std::cout << "comparison_expression -> additive_expression NE_OP additive_expression" << std::endl;
		Node* tmp = new Node();
		tmp->addChild(*stackForTree.front()); 
		stackForTree.pop_front();
		tmp->addChild(*(new Node("!=")));
		tmp->addChild(*stackForTree.front()); 
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
;

expression
: IDENTIFIER '=' comparison_expression {std::cout << "expression -> IDENTIFIER = comparison_expression" << std::endl;
		Node* tmp = new Node(ID_EXPRESSION);
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		tmp->addChild(*(new Node("=")));
		tmp->addChild(*(new Node($1)));
		stackForTree.push_front(tmp);
		}
| IDENTIFIER '[' expression ']' '=' comparison_expression {std::cout << "expression -> IDENTIFIER [expression] = comparison_expression" << std::endl;
		Node* tmp = new Node($1, ID_EXPRESSION);
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		tmp->addChild(*(new Node("] = ")));
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		tmp->addChild(*(new Node("[")));
		stackForTree.push_front(tmp);
		}
| comparison_expression {std::cout << "expression -> comparison_expression " << std::endl;}
;

declaration
: type_name declarator_list ';' {std::cout << "declaration -> type_name declarator_list" << std::endl;
		Node* tmp = new Node(ID_DECLARATION);
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
;

declarator_list
: declarator {std::cout << "declarator_list -> declarator" << std::endl;}
| declarator_list ',' declarator {std::cout << "declarator_list -> declarator_list, declarator" << std::endl;
		Node* tmp = new Node();
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		tmp->addChild(*(new Node(",")));
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
;

type_name
: VOID  {std::cout << "type_name -> VOID " << std::endl; 
		stackForTree.push_front(new Node("VOID ", ID_TYPE));
	}
| INT   {std::cout << "type_name -> INT" << std::endl;
		stackForTree.push_front(new Node("INT ", ID_TYPE));
	}
| FLOAT {std::cout << "type_name -> FLOAT" << std::endl;
		stackForTree.push_front(new Node("FLOAT ", ID_TYPE));
	}
;
;

declarator
: IDENTIFIER   {std::cout << "declarator -> IDENTIFIER" << std::endl;
		stackForTree.push_front(new Node($1, ID_DECLARATOR));
		}
| '*' IDENTIFIER {std::cout << "declarator -> * IDENTIFIER" << std::endl;
		//FIXME Don't know the problem stackForTree.push_front(new Node(std::string('*') + std::string($1)));
		}
| IDENTIFIER '[' ICONSTANT ']' {std::cout << "declarator -> IDENTIFIER [ ICONSTANT ]" << std::endl;
		stackForTree.push_front(new Node($1, ID_DECLARATOR));
		}
| declarator '(' parameter_list ')' {std::cout << "declarator -> declarator (parameter_list )" << std::endl;
		Node* tmp = new Node(ID_DECLARATOR);
		tmp->addChild(*(new Node(")")));
		tmp->addChild(*stackForTree.front()); //Take decarator as child
		stackForTree.pop_front();
		tmp->addChild(*(new Node("(")));
		tmp->addChild(*stackForTree.front()); //Take parameter_list as child
		stackForTree.pop_front();
		stackForTree.push_front(tmp); //Put this declarator without value
		}
| declarator '(' ')' {std::cout << "declarator -> declarator ()" << std::endl;
		Node* tmp = new Node(ID_DECLARATOR);
		tmp->addChild(*(new Node(" ()")));
		tmp->addChild(*stackForTree.front()); //Take decarator as child
		stackForTree.pop_front();
		stackForTree.push_front(tmp); //Put this declarator without value
		}
;

parameter_list
: parameter_declaration {std::cout << "parameter_list -> parameter_declaration" << std::endl;}
| parameter_list ',' parameter_declaration {std::cout << "parameter_list -> parameter_list , parameter_declaration" << std::endl;
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
: type_name declarator {std::cout << "parameter_declaration -> type_name declarator" << std::endl;
		Node* tmp = new Node();
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
;

statement
: compound_statement {std::cout << "statement -> compound_statement" << std::endl;
		stackForTree.front()->setId(ID_STATEMENT);
		}
| expression_statement  {std::cout << "statement -> expression_statement" << std::endl;
		stackForTree.front()->setId(ID_STATEMENT);
		}
| selection_statement {std::cout << "statement -> selection_statement" << std::endl;
		stackForTree.front()->setId(ID_STATEMENT);
		}
| iteration_statement {std::cout << "statement -> iteration_statement" << std::endl;
		stackForTree.front()->setId(ID_STATEMENT);
		}
| jump_statement {std::cout << "statement -> jump_statement" << std::endl;
		stackForTree.front()->setId(ID_STATEMENT);
		}
;

compound_statement
: '{' '}' {std::cout << "compound_statement ->  { }" << std::endl;
		Node* tmp = new Node("{ }", ID_COUMPOUND_STATEMENT);
		stackForTree.push_front(tmp);
		}
| '{' statement_list '}' {std::cout << "compound_statement -> { statement_list }" << std::endl;
		Node* tmp = new Node(ID_COUMPOUND_STATEMENT);
		tmp->addChild(*(new Node("\n}\n")));
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		tmp->addChild(*(new Node("\n{\n")));
		stackForTree.push_front(tmp);
		}
| '{' declaration_list statement_list '}' {std::cout << "compound_statement -> { declaration_list statement_list }" << std::endl;
		Node* tmp = new Node(ID_COUMPOUND_STATEMENT);
		tmp->addChild(*(new Node("\n}\n")));
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		tmp->addChild(*(new Node("\n{\n")));
		stackForTree.push_front(tmp);
		}
;

declaration_list
: declaration {std::cout << "declaration_list -> declaration" << std::endl;}
| declaration_list declaration {std::cout << "declaration_list -> declaration_list declaration" << std::endl;
		Node* tmp = new Node();
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
;

statement_list
: statement {std::cout << "statement_list -> statement" << std::endl;}
| statement_list statement {std::cout << "statement_list -> statement_list statement" << std::endl;
		Node* tmp = new Node(ID_STATEMENT_LIST);
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
;

expression_statement
: ';' {std::cout << "expression_statement -> ;" << std::endl;}
| expression ';' {std::cout << "expression_statement -> expression ;" << std::endl;
		Node* tmp = new Node();
		tmp->addChild(*(new Node(";\n")));
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
;

selection_statement
: IF '(' expression ')' statement {std::cout << "selection_statement -> IF ( expression ) statement" << std::endl;
		Node* tmp = new Node("IF (");
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		tmp->addChild(*(new Node(")\n")));
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
| IF '(' expression ')' statement ELSE statement {std::cout << "selection_statement -> IF ( expression ) statement ELSE statement" << std::endl;
		Node* tmp = new Node();
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		tmp->addChild(*(new Node(" \nELSE\n ")));
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		tmp->addChild(*(new Node(") ")));
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		tmp->addChild(*(new Node("IF (")));
		stackForTree.push_front(tmp);
		}
;

iteration_statement
: WHILE '(' expression ')' statement {std::cout << "iteration_statement -> WHILE ( expression ) statement" << std::endl;
		Node* tmp = new Node("WHILE (");
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		tmp->addChild(*(new Node(")")));
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
| FOR '(' expression_statement expression_statement expression ')' statement {std::cout << "iteration_statement -> FOR ( expression_statement expression_statement expression ) statement" << std::endl;
		Node* tmp = new Node();
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		tmp->addChild(*(new Node(")")));
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		tmp->addChild(*(new Node("\nFOR (")));
		stackForTree.push_front(tmp);
		}
;

jump_statement
: RETURN ';' {std::cout << "jump_statement -> RETURN ;" << std::endl;
		Node* tmp = new Node("RETURN ;");
		stackForTree.push_front(tmp);
		}
| RETURN expression ';' {std::cout << "jump_statement -> RETURN expression ;" << std::endl;
		Node* tmp = new Node("RETURN ");
		tmp->addChild(*(new Node(";\n")));
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
;

program
: external_declaration {std::cout << "program -> external_declaration" << std::endl;}
| program external_declaration {std::cout << "program -> program external_declaration" << std::endl;
		Node* tmp = new Node(ID_EXTERNAL_DECLARATION);
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		tmp->addChild(*stackForTree.front());
		stackForTree.pop_front();
		stackForTree.push_front(tmp);
		}
;

external_declaration
: function_definition {std::cout << "external_declaration -> function_definition" << std::endl;}
| declaration {std::cout << "external_declaration -> declaration" << std::endl;
		stackForTree.front()->setId(ID_GLOBAL_DECLARATOR);
		}
;

function_definition
: type_name declarator compound_statement {std::cout << "function_definition -> type_name declarator compound_statement" << std::endl;
		Node* body = stackForTree.front();
		stackForTree.pop_front();
		Node* argument = stackForTree.front();
		stackForTree.pop_front();
		Node * type = stackForTree.front(); 
		stackForTree.pop_front();
		Node* tmp = new Function(*type, *argument, *body);
		tmp->addChild(*body);
		tmp->addChild(*argument);
		tmp->addChild(*type);
		stackForTree.push_front(tmp);
		}
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
		/*std::cout << std::endl << stackForTree.size() << std::endl;*/
		/*stackForTree.front()->flattenFunction();*/
		stackForTree.front()->printTree(0, 20);
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
