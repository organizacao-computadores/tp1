#ifndef PROGRAMAS_H
#define PROGRAMAS_H

#include "ram.h"
#include "cpu.h"
#include "instrucao.h"

int programaMulti(CPU *cpu, int a, int b);
int programaDiv(CPU *cpu, int dividendo, int divisor);
int programaRaizAproximada(CPU *cpu, int valor);
int programaFatorial(CPU *cpu, int valor);
int programaExponencial(CPU *cpu, int base, int expoente);
int programaBhaskara(CPU *cpu, int a, int b, int c, int *res);
int programaLog(CPU *cpu, int base, int logaritmando);
RAM *programaPreencheMatriz(CPU *cpu, RAM *ram, int pontoDePartida, int n, int m);
RAM *programaMultiplicaMatriz(CPU *cpu, RAM *ram, int n1, int m1, int n2, int m2);
void imprimirMatriz(CPU *cpu, RAM *ram, int pontoDePartida, int n, int m);
RAM *criaMatriz(int n, int m, RAM *ram);
int programaRaizCubicaAroximada(CPU *cpu, int valor);
int programaTermoPA(CPU *cpu, int a1, int n, int r);

#endif