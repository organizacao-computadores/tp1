#ifndef PROGRAMAS_H
#define PROGRAMAS_H

#include "ram.h"
#include "cpu.h"
#include "instrucao.h"

int programaMulti(CPU *cpu, int a, int b);
int programaDiv(CPU *cpu, int dividendo, int divisor);
int programaRaizAproximada(CPU *cpu, int valor);
int programaFatorial(CPU *cpu, int valor);
void programaBhaskara(CPU *cpu, int a, int b, int c, int *res);
RAM *programaPreencheMatriz(CPU *cpu, RAM *ram, int n, int m);
RAM *programaMultiplicaMatriz(CPU *cpu, RAM *matriz1, int n1, int m1, RAM *matriz2, int n2, int m2);


#endif