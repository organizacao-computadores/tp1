#include <stdio.h>
#include <stdlib.h>

#include "programas.h"

int encontrarPosicaoMatriz(int posInicial, int nLinhas, int mColunas, int i, int j);
RAM *criaMatriz(int n, int m, RAM *ram);

int programaMulti(CPU *cpu, int a, int b){
  int result;
  RAM *ram = criarRAM_vazia(2);
  Instruction **trecho1;
  trecho1 = (Instruction**) malloc(3 * sizeof(Instruction*));

  trecho1[0] = setInstruction(1, a, -1, 4); //reg1 <- a
  trecho1[1] = setInstruction(1, 1, -1, 2); //ram[1] <- reg1
  trecho1[2] = setInstruction(-1, -1, -1, -1); //halt

  setPrograma(cpu, trecho1, 3);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 3);

  trecho1 = destroiTrecho(trecho1, 3);

  Instruction **trecho2;
  trecho2 = (Instruction**) malloc(2 * sizeof(Instruction*));
  for(int i = 0; i < b; i++){ //ram[0] += ram[1](a); (b) vezes
    trecho2[0] = setInstruction(0, 1, 0, 0); //reg1 <- ram[0]; reg2 <- ram[1]; reg1 += reg2; ram[0] <- reg1
    trecho2[1] = setInstruction(-1, -1, -1, -1); //halt

    setPrograma(cpu, trecho2, 2);
    iniciar(cpu, ram);
    destroiPrograma(cpu, 2);
  }

  trecho2 = destroiTrecho(trecho2, 2);

  result = getDado(0, ram);
  ram = liberarRAM(2, ram);

  return result;
}

int programaDiv(CPU *cpu, int dividendo, int divisor){
  RAM *ram = criarRAM_vazia(5);

  Instruction **trecho1 = (Instruction **) malloc(5 * sizeof(Instruction*));
  trecho1[0] = setInstruction(1, dividendo, -1, 4); //reg1 <- dividendo
  trecho1[1] = setInstruction(1, 0, -1, 2); //ram[0] <- reg1
  trecho1[2] = setInstruction(2, divisor, -1, 4); //reg 2 <- divisor
  trecho1[3] = setInstruction(2, 1, -1, 2); //ram[1] <- reg2
  trecho1[4] = setInstruction(-1, -1, -1, -1); //halt

  setPrograma(cpu, trecho1, 5);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 5);

  trecho1 = destroiTrecho(trecho1, 5);

  Instruction **trecho2 = (Instruction **) malloc(3 * sizeof(Instruction*));
  trecho2[0] = setInstruction(1, 1, -1, 4); //reg1 <- 1
  trecho2[1] = setInstruction(1, 2, -1, 2); //ram[2] <- reg1
  trecho2[2] = setInstruction(-1, -1, -1, -1); //halt

  setPrograma(cpu, trecho2, 3);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 3);


  trecho2 = destroiTrecho(trecho2, 3);

  Instruction **trecho3 = (Instruction **) malloc(5 * sizeof(Instruction*));

  while(dividendo >= divisor){

    trecho3[0] = setInstruction(0, 1, 0, 1); //reg1 <- ram[0]; reg2 <- ram[1]; reg1 -= reg2; ram[0] <- reg1;
    trecho3[1] = setInstruction(2, 3, 3, 0); //reg1 <- ram[2]; reg2 <- ram[3]; reg1 += reg2; ram[3] <- reg1;
    trecho3[2] = setInstruction(1, 0, -1, 3); //reg1 <- ram[0];
    trecho3[3] = setInstruction(1, 4, -1, 5); //ram[4] <- reg1;
    trecho3[4] = setInstruction(-1, -1, -1, -1); //halt

    setPrograma(cpu, trecho3, 5);
    iniciar(cpu, ram);
    destroiPrograma(cpu, 5);

    dividendo = getDado(4, ram);

  }

  trecho3 = destroiTrecho(trecho3, 5);

  Instruction **trecho4 = (Instruction **) malloc(3 * sizeof(Instruction*));
  trecho4[0] = setInstruction(1, 3, -1, 3); //reg1 <- ram[3]
  trecho4[1] = setInstruction(1, 4, -1, 5); //ram[4] <- reg1
  trecho4[2] = setInstruction(-1, -1, -1, -1); //halt

  setPrograma(cpu, trecho4, 3);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 3);


  int result = getDado(4, ram);

  trecho4 = destroiTrecho(trecho4, 3);

  ram = liberarRAM(5, ram);

  return result;

}

int programaRaizAproximada(CPU *cpu, int valor) {
  RAM *ram = criarRAM_vazia(2);

  //cria um vetor de instruções
  Instruction **trecho = (Instruction **) malloc(3 * sizeof(Instruction *));
  
  // multiplica i^2 até o resultado ser maior ou igual que o valor digitado
  int aux = 0;
  int i = 1;

  while (aux <= valor) {
    aux = programaMulti(cpu, i, i);
    
    trecho[0] = setInstruction(1, aux, -1, 4); // envia aux para o registrador 1
    trecho[1] = setInstruction(1, 0, -1, 5); // passa valor do registrador 1 (aux) para a ram[0]
    trecho[2] = setInstruction(-1, -1, -1, -1); // haut

    setPrograma(cpu, trecho, 3); // envia as instruções para a cpu
    iniciar(cpu, ram); // executa as instruções na cpu
    destroiPrograma(cpu, 3); // free no programa criado

    i++;
  }
 
  // libera memória alocada
  trecho = destroiTrecho(trecho, 3);
  liberarRAM(2, ram);

  return i-2;
}

int encontrarPosicaoMatriz(int posInicial, int nLinhas, int mColunas, int i, int j){
  int endereco;
  endereco = (posInicial + i * mColunas + j);
  return endereco;
}

RAM *criaMatriz(int n, int m, RAM *ram){
  ram = criarRAM_vazia(n * m);
  return ram;
}

RAM *programaPreencheMatriz(CPU *cpu, RAM *ram, int n, int m){
  int temp, endereco;
  ram = criaMatriz(n, m, ram);

  Instruction **trecho = (Instruction **) malloc(3 * sizeof(Instruction*));

  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      endereco = encontrarPosicaoMatriz(0, n, m, i, j);
      printf("\nInsira o valor da matriz[%d][%d]: ", i, j);
      scanf("%d", &temp);

      trecho[0] = setInstruction(1, temp, -1, 4);
      trecho[1] = setInstruction(1, endereco, -1, 5);
      trecho[2] = setInstruction(-1, -1, -1, -1);

      setPrograma(cpu, trecho, 3);
      iniciar(cpu, ram);
      destroiPrograma(cpu, 3);
    }
  }

  imprimir(ram);

  trecho = destroiTrecho(trecho, 3);

  return ram;
}

RAM *programaMultiplicaMatriz(CPU *cpu, RAM *matriz1, int n1, int m1, RAM *matriz2, int n2, int m2){
  int addResult, addM1, addM2, tempMult;
  RAM *resultado;
  resultado = criarRAM_vazia(m1 * n2);

  Instruction **trecho = (Instruction **) malloc(2 * sizeof(Instruction *));

  for(int i = 0; i < n1; i++){
    for(int j = 0; j < m2; j++){
      addResult = encontrarPosicaoMatriz(0, m1, n2, i, j);
      for(int k = 0; k < m1; k++){

          addM1 = encontrarPosicaoMatriz(0, n1, m1, i, k);
          addM2 = encontrarPosicaoMatriz(0, n2, m2, k, j);

          tempMult = programaMulti(cpu, getDado(addM1, matriz1), getDado(addM2, matriz2));

          trecho[0] = setInstruction(tempMult, getDado(addResult, resultado), addResult, 0);
          trecho[1] = setInstruction(-1, -1, -1, -1);

          setPrograma(cpu, trecho, 2);
          iniciar(cpu, resultado);
          destroiPrograma(cpu, 2);
      }
    }
  }

  trecho = destroiTrecho(trecho, 2);

  return resultado;

}

int programaFatorial(CPU *cpu, int valor) {
  RAM *ram = criarRAM_vazia(2);

  //cria um vetor de instruções
  Instruction **trecho = (Instruction **) malloc(3 * sizeof(Instruction *));

  //multiplica todos os valores de 'valor' até '2'
  int aux = valor;
  for (int i = valor-1; i > 1; i--) {
    aux = programaMulti(cpu, aux, i);

    trecho[0] = setInstruction(1, aux, -1, 4); // envia res para o registrador 1
    trecho[1] = setInstruction(1, 0, -1, 5); // passa valor do registrador 1 (aux) para a ram[0]
    trecho[2] = setInstruction(-1, -1, -1, -1); // haut

    setPrograma(cpu, trecho, 3); // envia as instruções para a cpu
    iniciar(cpu, ram); // executa as instruções na cpu
    destroiPrograma(cpu, 3); // free no programa criado    
  }

  // free nas memórias alocadas
  liberarRAM(2, ram);
  destroiTrecho(trecho, 3);

  return aux;
}

//teste branch