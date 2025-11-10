#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ram.h"
#include "cpu.h"
#include "instrucao.h"
#include "programas.h"

void programas();

int main() {
	srand(time(NULL));

	int n;
	printf("Insira o tamanho da memória: ");
	scanf("%d", &n);

	RAM *ram = criarRAM_aleatoria(n);
	printf("\nRam aleatoria gerada: \n");
	imprimir(ram);

	liberarRAM(n, ram);

	programas();

}

void programas(){
	//RAM *ram;
	CPU *cpu;
	int a, b;

	cpu = criarCPU();
	//ram = criarRAM_vazia(1);

	printf("\nInsira a e b para multiplicação: \n");
	scanf("%d%d", &a, &b);

	printf("\nAxB = %d\n", programaMulti(cpu, a, b));

	printf("\nInsira a e b para divisão: \n");
	scanf("%d%d", &a, &b);

	printf("\nA/B = %d\n", programaDiv(cpu, a, b));

	printf("\nInsira a para cálculo da raiz: \n");
	scanf("%d", &a);

	printf("\nRaiz de a = %d\n", programaRaizAproximada(cpu, a));

	int n1, m1, n2, m2;

	printf("\nInsira n e m para criar uma matriz: \n");
	scanf("%d%d", &n1, &m1);

	RAM *ramMatriz1;
	ramMatriz1 = programaPreencheMatriz(cpu, ramMatriz1, n1, m1);

	printf("\nResultado da matriz preenchida:\n");
	imprimir(ramMatriz1);

	printf("\nInsira n e m para criar outra matriz: \n");
	scanf("%d%d", &n2, &m2);

	RAM *ramMatriz2;
	ramMatriz2 = programaPreencheMatriz(cpu, ramMatriz2, n2, m2);

	printf("\nResultado da matriz preenchida:\n");
	imprimir(ramMatriz2);

	RAM *resultadoMultMatrizes;
	resultadoMultMatrizes = programaMultiplicaMatriz(cpu, ramMatriz1, n1, m2, ramMatriz2, n2, m2);

	printf("\nMatriz1 X Matriz2:\n");
	imprimir(resultadoMultMatrizes);

	ramMatriz1 = liberarRAM(n1 * m1, ramMatriz1);
	ramMatriz2 = liberarRAM(n2 * m2, ramMatriz2);
	resultadoMultMatrizes = liberarRAM(m1 * n2, resultadoMultMatrizes);


	free(cpu);
}