#include <list>
#include <map>
class Instruction;

class Function
{
	std::list<Instruction*> allInstruction;

	//Contain all offset of the variable in the stack frame
	std::map<std::string, int> allVariableOffset;
	public:
		void printAsm(int fd);	
};
