#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ram.h"
#include "cpu.h"
#include "instrucao.h"
#include "programas.h"

#define TAMANHO_RAM 1000

void programas();

int main() {
	srand(time(NULL));

	programas();

	return 0;
}

void programas(){

	RAM *ram = criarRAM_vazia(TAMANHO_RAM);
	CPU *cpu;
	int a, b, c, n;

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
				RAM *tempRam =	criarRAM_aleatoria(n);
				printf("\nRam aleatoria gerada: \n");
				imprimir(tempRam);
				tempRam = liberarRAM(tempRam);
				break;
			//mult
			case 2:
				printf("\nInsira dois valores para multiplicação: ");
				scanf("%d%d", &a, &b);
				printf("%d x %d = %d\n", a, b, programaMulti(cpu, ram, 0, a, b));
				
				break;
				
			//div
			case 3:
				printf("\nInsira dois valores para divisão inteira: ");
				scanf("%d%d", &a, &b);
				printf("%d / %d = %d\n", a, b, programaDiv(cpu, ram, 0, a, b));

				break;
				
			//mod	
			case 4:
				printf("\nInsira A e B para obter o módulo entre eles: ");
				scanf("%d %d", &a, &b);
				printf("\nO módulo de A/B = %d\n", programaModulo(cpu, ram, 0, a, b));

				break;
				
			//par
			case 5:
				printf("\nInsira um valor para verificar se é par: ");
				scanf("%d", &a);
				printf("%d %sé par\n", a, programaEhPar(cpu, ram, 0, a) ? "" : "não " );

				break;
				
			//primo
			case 6:
				printf("\nInsira um número para verificar se ele é primo: ");
				scanf("%d", &a);
				printf("O número %d %sé primo\n", a, programaEhNumeroPrimo(cpu, ram, 0, a) ? "" : "não " );

				break;
				
			//raiz quadr
			case 7:
				printf("\nInsira um valor para calcular sua raiz quadrada aproximada: ");
				scanf("%d", &a);
				printf("Raiz quadrada de %d = %d\n", a, programaRaizAproximada(cpu, ram, 0, a));

				break;
				
			//raiz cub
			case 8:
				printf("\nInsira um valor para calcular sua raiz cubica aproximada: ");
				scanf("%d", &a);
				printf("Raiz cubica de %d = %d\n", a, programaRaizCubicaAroximada(cpu, ram, 0, a));

				break;
				
			//fat
			case 9:
				printf("\nDigite um valor para calcular seu fatorial: ");
				scanf("%d", &a);
				printf("Fatorial de %d = %d\n", a, programaFatorial(cpu, ram, 0, a));

				break;
				
			//exp
			case 10:
				printf("\nDigite base e expoente para calcular exponenciação: ");
				scanf("%d%d", &a, &b);
				printf("%d ^ %d = %d\n", a, b, programaExponencial(cpu, ram, 0, a, b));

				break;
				
			//log
			case 11:
				printf("\nDigite base e logaritmando: ");
				scanf("%d%d", &a, &b);
				printf("log(%d, %d) = %d\n", a, b, programaLog(cpu, ram, 0, a, b));

				break;
			
			//mdc
			case 12:
				printf("\nInsira dois valores para o cálculo do MDC: ");
				scanf("%d%d", &a, &b);
				printf("MDC entre %d e %d = %d\n", a, b, programaMdc(cpu, ram, 0, a, b));

				break;
				
			//mmc
			case 13:
				printf("\nInsira dois valores para o cálculo do MMC: ");
				scanf("%d%d", &a, &b);
				printf("MMC entre %d e %d = %d\n", a, b, programaMmc(cpu, ram, 0, a, b));

				break;
				
			//bhaskara
			case 14:
				printf("\nDigite a, b e c para calcular a fórmula de bháskara: ");
				scanf("%d%d%d", &a, &b, &c);
				int aux = programaBhaskara(cpu, ram, 0, a, b, c, 40);

				if (aux) {
					printf("X1 = %d\nX2 = %d\n", getDado(40, ram), getDado(41, ram));
				}
				else {
					printf("Delta negativo! Sem raízes reais!\n");
				}
				
				break;
				
			//fibonacci
			case 15:
				printf("\nDigite até qual elemento da sequência de fibonacci você deseja: ");
				scanf("%d", &a);

				programaFibonacci(cpu, ram, 0, a);

				printf("\nSequência Fibonacci até %dº elemento:\n", a);
				for(int i = 0; i < a; i++){
					printf("%d ", getDado(i, ram));
				}
				printf("\n");
				ram = zerarRAM(ram, 0, a);
				break;
				
			//n termo da pa
			case 16:
				int a1, n, r;
				printf("\nInsira a1, n e r para calcular o n-ésimo termo da PA: ");
				scanf("%d %d %d", &a1, &n, &r);
				printf("\nn-ésimo termo = %d\n", programaTermoPA(cpu, ram, 0, a1, n, r));
				
				break;
				
			//soma da pa
			case 17:
				printf("\nInsira a1, n e r para calcular a soma dos termos da PA: ");
				scanf("%d %d %d", &a1, &n, &r);
				printf("\nSoma dos termos = %d\n", programaSomaTermosPA(cpu, ram, 0, a1, n, r));
				
				break;
				
			//mult de mat
			case 18:
				int n1, m1, n2, m2;
				printf("\nInsira n e m para criar a primeira matriz: ");
				scanf("%d%d", &n1, &m1);

				ram = programaPreencheMatriz(cpu, ram, TAMANHO_RAM - 2, 0, n1, m1);
				int tamM1 =  programaMulti(cpu, ram, TAMANHO_RAM - 2 , n1, m1);

				printf("\nInsira n e m para criar a segunda matriz: ");
				scanf("%d%d", &n2, &m2);

				ram = programaPreencheMatriz(cpu, ram, TAMANHO_RAM - 2, tamM1, n2, m2);

				printf("\nResultante de Matriz1 x Matriz2:\n");
				ram = programaMultiplicaMatriz(cpu, ram, TAMANHO_RAM - 6, 0, n1, m1, n2, m2);
				
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