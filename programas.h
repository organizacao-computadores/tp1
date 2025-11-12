#ifndef PROGRAMAS_H
#define PROGRAMAS_H

#include<stdbool.h>

#include "ram.h"
#include "cpu.h"
#include "instrucao.h"

int programaMulti(CPU *cpu, int a, int b);
int programaDiv(CPU *cpu, int dividendo, int divisor);
int programaModulo(CPU *cpu, int a, int b);
int programaRaizAproximada(CPU *cpu, int valor);
int programaRaizCubicaAroximada(CPU *cpu, int valor);
int programaFatorial(CPU *cpu, int valor);
int programaExponencial(CPU *cpu, int base, int expoente);
int programaLog(CPU *cpu, int base, int logaritmando);
int programaMdc(CPU *cpu, int a, int b);
int programaMmc(CPU *cpu, int a, int b);
int programaBhaskara(CPU *cpu, int a, int b, int c, int *res);
bool programaEhNumeroPrimo(CPU *cpu, int valor);
bool ehPar(CPU *cpu, int a);


RAM *programaPreencheMatriz(CPU *cpu, RAM *ram, int pontoDePartida, int n, int m);
RAM *programaMultiplicaMatriz(CPU *cpu, RAM *ram, int n1, int m1, int n2, int m2);
void imprimirMatriz(CPU *cpu, RAM *ram, int pontoDePartida, int n, int m);
RAM *criaMatriz(int n, int m, RAM *ram);


RAM *programaFibonacci(CPU *cpu, RAM *ram,int n);
int programaTermoPA(CPU *cpu, int a1, int n, int r);
int programaSomaTermosPA(CPU *cpu, int a1, int n, int r);

#endif