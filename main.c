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

	programas();

	return 0;
}

void programas(){
	RAM *ram = NULL;
	CPU *cpu;
	int a, b, c, n;
	int res[2];

	cpu = criarCPU();
	int op;

	while (true) {

		// imprimindo menu
		system("clear");
		printf("======================= PROGRAMAS IMPLEMENTADOS =======================\n");
		printf(" 0 - Encerrar Programa\n");
		printf(" 1 - Ram Aleatória\n");
		printf(" 2 - Multiplicação\n");
		printf(" 3 - Divisão Inteira\n");
		printf(" 4 - Módulo\n");
		printf(" 5 - É Par?\n");
		printf(" 6 - É Primo?\n");
		printf(" 7 - Raíz Quadrada Aproximada\n");
		printf(" 8 - Raíz Cúbica Aproximada\n");
		printf(" 9 - Fatorial\n");
		printf("10 - Exponenciação\n");
		printf("11 - Logaritmo\n");
		printf("12 - MDC\n");
		printf("13 - MMC\n");
		printf("14 - Bhaskara\n");
		printf("15 - Fibonacci\n");
		printf("16 - N-esimo termo da PA\n");
		printf("17 - Soma dos Termos da PA\n");
		printf("18 - Multiplicação de Matrizes\n");
		printf("=====================================================================");

		printf("\nSelecione o código da operação a ser realizada: ");
		scanf("%d", &op);

		// selecionando opção digitada
		switch(op) {
			//sair
			case 0:
				printf("\nPrograma encerrado!!!\n");
				break;
			case 1:
				printf("Insira o tamanho da memória: ");
				scanf("%d", &n);
				ram =	criarRAM_aleatoria(n);
				printf("\nRam aleatoria gerada: \n");
				imprimir(ram);
				break;
			//mult
			case 2:
				printf("\nInsira dois valores para multiplicação: ");
				scanf("%d%d", &a, &b);
				printf("%d x %d = %d\n", a, b, programaMulti(cpu, a, b));
				
				break;
				
			//div
			case 3:
				printf("\nInsira dois valores para divisão inteira: ");
				scanf("%d%d", &a, &b);
				printf("%d / %d = %d\n", a, b, programaDiv(cpu, a, b));

				break;
				
			//mod	
			case 4:
				printf("\nInsira A e B para obter o módulo entre eles: ");
				scanf("%d %d", &a, &b);
				printf("\nO módulo de A/B = %d\n", programaModulo(cpu, a, b));

				break;
				
			//par
			case 5:
				printf("\nInsira um valor para verificar se é par: ");
				scanf("%d", &a);
				printf("%d %sé par", a, programaEhPar(cpu, a) ? "" : "não " );

				break;
				
			//primo
			case 6:
				printf("\nInsira um número para verificar se ele é primo: ");
				scanf("%d", &a);
				printf("O número %d %sé primo\n", a, programaEhNumeroPrimo(cpu, a) ? "" : "não " );

				break;
				
			//raiz quadr
			case 7:
				printf("\nInsira um valor para calcular sua raiz quadrada aproximada: ");
				scanf("%d", &a);
				printf("Raiz quadrada de %d = %d\n", a, programaRaizAproximada(cpu, a));

				break;
				
			//raiz cub
			case 8:
				printf("\nInsira um valor para calcular sua raiz cubica aproximada: ");
				scanf("%d", &a);
				printf("Raiz cubica de %d = %d\n", a, programaRaizCubicaAroximada(cpu, a));

				break;
				
			//fat
			case 9:
				printf("\nDigite um valor para calcular seu fatorial: ");
				scanf("%d", &a);
				printf("Fatorial de %d = %d\n", a, programaFatorial(cpu, a));

				break;
				
			//exp
			case 10:
				printf("\nDigite base e expoente para calcular exponenciação: ");
				scanf("%d%d", &a, &b);
				printf("%d ^ %d = %d\n", a, b, programaExponencial(cpu, a, b));

				break;
				
			//log
			case 11:
				printf("\nDigite base e logaritmando: ");
				scanf("%d%d", &a, &b);
				printf("log(%d, %d) = %d\n", a, b, programaLog(cpu, a, b));

				break;
			
			//mdc
			case 12:
				printf("\nInsira dois valores para o cálculo do MDC: ");
				scanf("%d%d", &a, &b);
				printf("MDC entre %d e %d = %d\n", a, b, programaMdc(cpu, a, b));

				break;
				
			//mmc
			case 13:
				printf("\nInsira dois valores para o cálculo do MMC: ");
				scanf("%d%d", &a, &b);
				printf("MMC entre %d e %d = %d\n", a, b, programaMmc(cpu, a, b));

				break;
				
			//bhaskara
			case 14:
				printf("\nDigite a, b e c para calcular a fórmula de bháskara: ");
				scanf("%d%d%d", &a, &b, &c);
				int aux = programaBhaskara(cpu, a, b, c, res);

				if (aux) {
					printf("X1 = %d\nX2 = %d\n", res[0], res[1]);
				}
				else {
					printf("Delta negativo! Sem raízes reais!\n");
				}
				
				break;
				
			//fibonacci
			case 15:
				printf("\nDigite até qual elemento da sequência de fibonacci você deseja: ");
				scanf("%d", &a);

				ram = criarRAM_vazia(1);
				programaFibonacci(cpu, ram, a);

				printf("\nSequência Fibonacci até %dº elemento:\n", a);
				for(int i = 0; i < a; i++){
					printf("%d ", getDado(i, ram));
				}
				printf("\n");

				break;
				
			//n termo da pa
			case 16:
				int a1, n, r;
				printf("\nInsira a1, n e r para calcular o n-ésimo termo da PA: ");
				scanf("%d %d %d", &a1, &n, &r);
				printf("\nn-ésimo termo = %d\n", programaTermoPA(cpu, a1, n, r));
				
				break;
				
			//soma da pa
			case 17:
				printf("\nInsira a1, n e r para calcular a soma dos termos da PA: ");
				scanf("%d %d %d", &a1, &n, &r);
				printf("\nSoma dos termos = %d\n", programaSomaTermosPA(cpu, a1, n, r));
				
				break;
				
			//mult de mat
			case 18:
				int n1, m1, n2, m2;
				printf("\nInsira n e m para criar a primeira matriz: ");
				scanf("%d%d", &n1, &m1);

				ram = NULL;
				ram = criaMatriz(n1, m1, ram);
				ram = programaPreencheMatriz(cpu, ram, 0, n1, m1);
				int tamM1 = getTamanho(ram);

				printf("\nInsira n e m para criar a segunda matriz: ");
				scanf("%d%d", &n2, &m2);

				int tamM2 = programaMulti(cpu, n2, m2);

				ram = aumentarRam(ram, tamM1 + tamM2);
				ram = programaPreencheMatriz(cpu, ram, tamM1, n2, m2);

				printf("\nResultante de Matriz1 x Matriz2:\n");
				ram = programaMultiplicaMatriz(cpu, ram, n1, m1, n2, m2);

				ram = liberarRAM(ram);
				
				break;
				
			default:
				printf("\nOperação não encontrada!\n");
				break;
		}

		if (!op) break;

		printf("\nPressione enter...");
		getchar();
		getchar();
	}
	
	
	//liberando memorias alocadas
	if (ram)
		ram = liberarRAM(ram);
	
	if (cpu)
		free(cpu);

	return;
}