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
	liberarRAM(ram);
	programas();

}

void programas(){
	RAM *ram;
	CPU *cpu;
	int a, b, c;
	int res[2];

	cpu = criarCPU();

	//multiplicação
	printf("\nInsira dois valores para multiplicação: ");
	scanf("%d%d", &a, &b);
	printf("%d x %d = %d\n", a, b, programaMulti(cpu, a, b));

	//divisão
	printf("\nInsira dois valores para divisão: ");
	scanf("%d%d", &a, &b);
	printf("%d / %d = %d\n", a, b, programaDiv(cpu, a, b));

	//raiz quadrada
	printf("\nInsira um valor para calcular sua raiz quadrada aproximada: ");
	scanf("%d", &a);
	printf("Raiz quadrada de %d = %d\n", a, programaRaizAproximada(cpu, a));

	int n1, m1, n2, m2;
	printf("\nInsira n e m para criar uma matriz: ");
	scanf("%d%d", &n1, &m1);

	ram = NULL;
	ram = criaMatriz(n1, m1, ram);
	ram = programaPreencheMatriz(cpu, ram, 0, n1, m1);
	int tamM1 = getTamanho(ram);

	printf("Resultado da matriz preenchida:\n");
	imprimir(ram);

	printf("\nInsira n e m para criar outra matriz: \n");
	scanf("%d%d", &n2, &m2);

	int tamM2 = programaMulti(cpu, n2, m2);

	ram = aumentarRam(ram, tamM1 + tamM2);
	ram = programaPreencheMatriz(cpu, ram, tamM1, n2, m2);

	printf("\nResultado da matriz preenchida:\n");
	imprimir(ram);

	printf("\nMatriz1 X Matriz2:\n");
	ram = programaMultiplicaMatriz(cpu, ram, n1, m1, n2, m2);

	ram = liberarRAM(ram);

	//fatorial
	printf("\nDigite um valor para calcular seu fatorial: ");
	scanf("%d", &a);
	printf("Fatorial de %d = %d\n", a, programaFatorial(cpu, a));

	//formula de bhaskara
	printf("\nDigite a, b e c para calcular a fórmula de bháskara: ");
	scanf("%d%d%d", &a, &b, &c);
	int aux = programaBhaskara(cpu, a, b, c, res);
	
	if (aux) {
		printf("X1 = %d\nX2 = %d\n", res[0], res[1]);
	}
	else {
		printf("Delta negativo! Sem raízes reais!\n");
	}

	//exponenciação
	printf("\nDigite base e expoente para calcular exponenciação: ");
	scanf("%d%d", &a, &b);
	printf("%d ^ %d = %d\n", a, b, programaExponencial(cpu, a, b));

	//logaritmo
	printf("\nDigite base e logaritmando para calcular: ");
	scanf("%d%d", &a, &b);
	printf("log(%d, %d) = %d\n", a, b, programaLog(cpu, a, b));

	//raiz cubica
	printf("\nInsira um valor para calcular sua raiz cubica aproximada: ");
	scanf("%d", &a);
	printf("Raiz cubica de %d = %d\n", a, programaRaizCubicaAroximada(cpu, a));

	// n-esimo termo da pa
	int a1, n, r;
	printf("\nInsira a1, n e r para calcular o n-ésimo termo da PA: ");
	scanf("%d %d %d", &a1, &n, &r);
	printf("\nn-ésimo termo = %d\n", programaTermoPA(cpu, a1, n, r));

	//fibonacci
	printf("\nDigite até qual elemento da sequência de fibonacci você deseja: ");
	scanf("%d", &a);

	ram = criarRAM_vazia(1);
	programaFibonacci(cpu, ram, a);

	printf("Sequência Fibonacci até %dº elemento:\n", a);
	for(int i = 0; i < a; i++){
		printf("%d ", getDado(i, ram));
	}
	printf("\n");

	// soma dos termos da pa
	printf("\nInsira a1, n e r para calcular a soma dos termos da PA: ");
	scanf("%d %d %d", &a1, &n, &r);
	printf("\nSoma dos termos = %d\n", programaSomaTermosPA(cpu, a1, n, r));

	// modulo
	printf("\nInsira A e B para obter o módulo entre eles: ");
	scanf("%d %d", &a, &b);
	printf("\nO módulo de A/B = %d\n", programaModulo(cpu, a, b));

	// numero primo
	printf("\nInsira um número para verificar se ele é primo: ");
	scanf("%d", &a);
	printf("O número %d %sé primo\n", a, programaEhNumeroPrimo(cpu, a) ? "" : "não " );

	// mdc
	printf("\nInsira dois valores para o cálculo do MDC: ");
	scanf("%d%d", &a, &b);
	printf("MDC entre %d e %d = %d\n", a, b, programaMdc(cpu, a, b));
	
	// mmc
	printf("\nInsira dois valores para o cálculo do MMC: ");
	scanf("%d%d", &a, &b);
	printf("MMC entre %d e %d = %d\n", a, b, programaMmc(cpu, a, b));
	
	// eh par
	printf("\nInsira um valor para verificar se é par: ");
	scanf("%d", &a);
	printf("%d é par? %s", a, ehPar(cpu, a) ? "Sim\n" : "Não\n" );
	
	ram = liberarRAM(ram);

	free(cpu);
}