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

	printf("\nInsira m e n para criar uma matriz: \n");
	scanf("%d%d", &a, &b);

	RAM *ram;
	ram = programaPreencheMatriz(cpu, ram, a, b);

	printf("\nResultado da matriz preenchida:\n");
	imprimir(ram);
	ram = liberarRAM(a * b, ram);


	free(cpu);
}