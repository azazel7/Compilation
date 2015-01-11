#include "PForStatement.hpp"
#include <sstream>
#include <stdexcept>

PForStatement::PForStatement(char* i1, Node& expressionInit, char* i2, Node& expressionCondition, char* i3, Node& statement): i1(i1), expressionInit(expressionInit), i2(i2), expressionCondition(expressionCondition), i3(i3), statement(statement)
{

}
void PForStatement::semanticsCheck(void)
{
    if (i1 != i2 || i1 != i3)
        throw std::invalid_argument("unique identifier required in pfor");
	expressionInit.semanticsCheck();
	expressionCondition.semanticsCheck();
	statement.semanticsCheck();
}
void PForStatement::generateCode(FILE * fd) const
{
	static int number = -1;
	number++;
    fprintf(fd, "mov $_pfor_thread%d, %%eax\n", number);
    fprintf(fd, "mov %%eax, __parallel_for_thread\n");
    fprintf(fd, "mov %%ebp, __parallel_for_ebp\n");
    fprintf(fd, "mov %%esp, __parallel_for_esp\n");
    fprintf(fd, "# ----\n");
    expressionCondition.generateCode(fd);
	expressionInit.generateCode(fd);
    fprintf(fd, "# ----\n");
    fprintf(fd, "call __run_parallel_for\n");
    fprintf(fd, "add $8, %%esp\n");
    fprintf(fd, "jmp _pfor_join%d\n", number);
	fprintf(fd, "_pfor_thread%d:\n", number);
    fprintf(fd, "push %%ebp\n");
    fprintf(fd, "push %%ebx\n");
    fprintf(fd, "mov __parallel_for_ebp, %%ebp\n");
    fprintf(fd, "mov 12(%%esp), %%ebx\n");
    fprintf(fd, "# ----\n");
    // à cet endroit, %ebx contient l'adresse de la variable
    //TODO utilisée par le pfor (unique à chaque thread, non partagée)
	statement.generateCode(fd);
    fprintf(fd, "# ----\n");
    fprintf(fd, "pop %%ebx\n");
    fprintf(fd, "pop %%ebp\n");
    fprintf(fd, "ret\n");
    fprintf(fd, "_pfor_join%d:\n", number);
    fprintf(fd, "movl __parallel_for_esp, %%esp\n");
    fprintf(fd, "movl $0, __parallel_for_thread\n");
    fprintf(fd, "movl $0, __parallel_for_ebp\n");
    fprintf(fd, "movl $0, __parallel_for_esp\n");
}
