#ifndef PROGRAMAS_H
#define PROGRAMAS_H

#include "ram.h"
#include "cpu.h"
#include "instrucao.h"

int programaMulti(RAM *ram, CPU *cpu, int a, int b);
int programaDiv(RAM *ram, CPU *cpu, int dividendo, int divisor);


#endif