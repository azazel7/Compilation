#include "Function.hpp"
#include "Instruction.hpp"

void Function::printAsm(int fd)
{
	for(Instruction* i : allInstruction)
		i->printAsm(fd);
}
