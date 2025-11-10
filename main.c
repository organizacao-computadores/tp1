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
	int a, b, c;
	int res[2];

	cpu = criarCPU();
	//ram = criarRAM_vazia(1);

	//multiplicação
	printf("\nInsira dois valores para multiplicação: \n");
	scanf("%d%d", &a, &b);
	printf("\n%d x %d = %d\n", a, b, programaMulti(cpu, a, b));

	//divisão
	printf("\nInsira dois valores para divisão: \n");
	scanf("%d%d", &a, &b);
	printf("\n%d / %d = %d\n", a, b, programaDiv(cpu, a, b));

	//raiz quadrada
	printf("\nInsira um valor para calcular sua raiz quadrada aproximada: \n");
	scanf("%d", &a);
	printf("\nRaiz quadrada de %d = %d\n", a, programaRaizAproximada(cpu, a));

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

	//fatorial
	printf("\nDigite um valor para calcular seu fatorial: ");
	scanf("%d", &a);
	printf("\nFatorial de %d = %d\n", a, programaFatorial(cpu, a));

	//formula de bhaskara
	printf("\nDigite a, b e c para calcular a fórmula de bháskara: ");
	scanf("%d%d%d", &a, &b, &c);
	programaBhaskara(cpu, a, b, c, res);
	printf("\nX1 = %d\nX2 = %d\n", res[0], res[1]);

	free(cpu);
}