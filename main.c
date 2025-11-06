#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ram.h"

int main() {
	srand(time(NULL));
		
	int n;
	printf("Insira o tamanho da memória: ");
	scanf("%d", &n);

	RAM *ram = criarRAM_aleatoria(n);
	imprimir(ram);
}
