#ifndef PROGRAMAS_H
#define PROGRAMAS_H

#include "ram.h"
#include "cpu.h"
#include "instrucao.h"

int programaMulti(CPU *cpu, int a, int b);
int programaDiv(CPU *cpu, int dividendo, int divisor);
int programaRaizAproximada(CPU *cpu, int valor);
RAM *programaPreencheMatriz(CPU *cpu, RAM *ram, int n, int m);


#endif