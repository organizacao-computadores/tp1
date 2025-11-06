#include <stdlib.h>

#include "instrucao.h"
#include "ram.h"

struct cpu {
	int reg1, reg2;
	int PC;
	Instruction *programa;
	int opcode;
};

void setPrograma(Instruction* programa) {
		
}
