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

	programas();

}

void programas(){
	RAM *ram;
	CPU *cpu;
	int a, b;

	cpu = criarCPU();
	ram = criarRAM(1);

	printf("\nInsira a e b: \n");
	scanf("%d%d", &a, &b);



	printf("\nAxB = %d\n", programaMulti(ram, cpu, a, b));

	printf("\nInsira a e b: \n");
	scanf("%d%d", &a, &b);

	printf("\nA/B = %d\n", programaDiv(ram, cpu, a, b));

	if(ram != NULL)
		free(ram);
	free(cpu);
}