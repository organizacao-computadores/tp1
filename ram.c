#include <stdio.h>
#include <stdlib.h>

#include "ram.h"

struct ram {
	int tamanho;
	int *memoria;
};

RAM* criarRAM(int tamanho) {
	RAM *ram = (RAM*) malloc(sizeof(RAM));
	ram->memoria = malloc(tamanho * sizeof(int));
	if (!ram->memoria) {
		printf("Erro de alocação.\n");
		return NULL;
	}
			
	ram->tamanho = tamanho;
	return ram;
}

RAM* criarRAM_vazia(int tamanho) {
	RAM *ram = criarRAM(tamanho);
	for (int i = 0; i < tamanho; i++)
		ram->memoria[i] = 0;

	return ram;
}

RAM* criarRAM_aleatoria(int tamanho) {
	RAM *ram = criarRAM(tamanho);
	for (int i = 0; i < tamanho; i++) 
		ram->memoria[i] = rand() % RAND_MAX;

	return ram;
}

void liberarRAM(int tamanho, RAM *ram) {
	free(ram->memoria);
	ram->memoria = NULL;
	ram->tamanho = 0;
}

void setDado(int endereco, int conteudo, RAM *ram) {
	ram->memoria[endereco] = conteudo;
}

int getDado(int endereco, RAM *ram) {
	return ram->memoria[endereco];	
}

void imprimir(RAM *ram) {
	printf("Conteúdo da RAM: \n");
	for (int i = 0; i < ram->tamanho; i++)
		printf("%d, ", ram->memoria[i]);
	printf("\n");
}