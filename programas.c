#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "programas.h"

int encontrarPosicaoMatriz(CPU *cpu, int posInicial, int nLinhas, int mColunas, int i, int j);


int programaMulti(CPU *cpu, int a, int b){
  int result;
  RAM *ram = criarRAM_vazia(2);
  Instruction **trecho1;
  trecho1 = (Instruction**) malloc(3 * sizeof(Instruction*));

  bool eraNeg1 = false;
  bool eraNeg2 = false;
  if (a < 0) {
    a = -a;
    eraNeg1 = true;
  }

  if (b < 0) {
    b = -b;
    eraNeg2 = true;
  } 

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
  ram = liberarRAM(ram);

  if (eraNeg1 && eraNeg2) {
    return result;
  }
  else if (!eraNeg1 && !eraNeg2) {
    return result;
  }
  else {
    return -result;
  }
}

int programaDiv(CPU *cpu, int dividendo, int divisor){
  RAM *ram = criarRAM_vazia(5);
  
  bool eraNeg1 = false;
  bool eraNeg2 = false;

  if (divisor < 0) {
    divisor = -divisor;
    eraNeg1 = true;
  }

  if (dividendo < 0) {
    dividendo = -dividendo;
    eraNeg2 = true;
  }

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

  ram = liberarRAM(ram);

  if (eraNeg1 && eraNeg2) {
    return result;
  }
  else if (!eraNeg1 && !eraNeg2) {
    return result;
  }
  else {
    return -result;
  }
}

int programaRaizAproximada(CPU *cpu, int valor) {
  RAM *ram = criarRAM_vazia(1);

  //cria um vetor de instruções
  Instruction **trecho = (Instruction **) malloc(3 * sizeof(Instruction *));
  
  // multiplica i^2 até o resultado ser maior ou igual que o valor digitado
  int aux = 0;
  int i = 1;

  while (aux <= valor) {
    aux = programaMulti(cpu, i, i);
    
    trecho[0] = setInstruction(1, aux, -1, 4); // envia aux para o registrador 1
    trecho[1] = setInstruction(1, 0, -1, 5); // passa valor do registrador 1 (aux) para a ram[0]
    trecho[2] = setInstruction(-1, -1, -1, -1); // halt

    setPrograma(cpu, trecho, 3); // envia as instruções para a cpu
    iniciar(cpu, ram); // executa as instruções na cpu
    destroiPrograma(cpu, 3); // free no programa criado

    i++;
  }

  // libera memória alocada
  trecho = destroiTrecho(trecho, 3);
  liberarRAM(ram);

  return i-2;
}

int encontrarPosicaoMatriz(CPU *cpu, int posInicial, int nLinhas, int mColunas, int i, int j){
  int endereco;
  endereco = (posInicial + programaMulti(cpu, i, mColunas) + j);
  return endereco;
}

RAM *criaMatriz(int n, int m, RAM *ram){
  ram = criarRAM_vazia(n * m);
  return ram;
}

RAM *programaPreencheMatriz(CPU *cpu, RAM *ram, int pontoDePartida,int n, int m){
  int temp, endereco;

  Instruction **trecho = (Instruction **) malloc(3 * sizeof(Instruction*));

  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      endereco = encontrarPosicaoMatriz(cpu, pontoDePartida, n, m, i, j);
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

  imprimirMatriz(cpu, ram, pontoDePartida, n, m);

  trecho = destroiTrecho(trecho, 3);

  return ram;
}

RAM *programaMultiplicaMatriz(CPU *cpu, RAM *ram, int n1, int m1, int n2, int m2){
  int addResult, addM1, addM2, tempMult, tamanhoM1, tamanhoM2;

  if (m2 != n1) {
    printf("Erro: número de colunas de A deve ser igual ao número de linhas de B.\n");
    return ram;
  }

  tamanhoM1 = programaMulti(cpu, n1, m1);
  tamanhoM2 = programaMulti(cpu, n2, m2);

  ram = aumentarRam(ram, getTamanho(ram) + programaMulti(cpu, n1, m2));

  RAM *tempSoma = criarRAM_vazia(2);
  Instruction **trecho = (Instruction **) malloc(6 * sizeof(Instruction *));

  for(int i = 0; i < n1; i++){
    for(int j = 0; j < m2; j++){
      addResult = encontrarPosicaoMatriz(cpu, (tamanhoM1 + tamanhoM2), n1, m2, i, j);
      for(int k = 0; k < m1; k++){

        addM1 = encontrarPosicaoMatriz(cpu, 0, n1, m1, i, k);
        addM2 = encontrarPosicaoMatriz(cpu, tamanhoM1, n2, m2, k, j);

        tempMult = programaMulti(cpu, getDado(addM1, ram), getDado(addM2, ram));

        trecho[0] = setInstruction(1, tempMult, -1, 4);
        trecho[1] = setInstruction(1, 0, -1, 5);
        trecho[2] = setInstruction(2, getDado(addResult, ram), -1, 4);
        trecho[3] = setInstruction(2, 1, -1, 5);
        trecho[4] = setInstruction(0, 1, 0, 0);
        trecho[5] = setInstruction(-1, -1, -1, -1);

        setPrograma(cpu, trecho, 6);
        iniciar(cpu, tempSoma);
        destroiPrograma(cpu, 6);

        setDado(addResult, getDado(0, tempSoma), ram);

      }
    }
  }

  trecho = destroiTrecho(trecho, 6);
  tempSoma = liberarRAM(tempSoma);

  imprimirMatriz(cpu, ram, (tamanhoM1 + tamanhoM2), n1, m2);
  return ram;
}

void imprimirMatriz(CPU *cpu, RAM *ram, int pontoDePartida, int n, int m){
  int endereco;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      endereco = encontrarPosicaoMatriz(cpu, pontoDePartida, n, m, i, j);
      printf("%d ", getDado(endereco, ram));
    }
    printf("\n");
  }
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
  liberarRAM(ram);
  destroiTrecho(trecho, 3);

  return aux;
}

int programaBhaskara(CPU *cpu, int a, int b, int c, int *res) {
  // criação de RAM temporária
  RAM *ram = criarRAM_vazia(2);

  // cria vetor de instruções
  Instruction **trecho = (Instruction **) malloc(3 * sizeof(Instruction *));

  
  // calculo de delta
  int delta = programaMulti(cpu, b, b) - programaMulti(cpu, 4, programaMulti(cpu, a, c));

  if (delta<0) {
    return 0;
  }
  else {
    // calculo de x1
    int x1 = programaDiv(cpu, (-b + programaRaizAproximada(cpu, delta) ), programaMulti(cpu, 2, a)); 

    trecho[0] = setInstruction(1, x1, -1, 4); // envia res para o registrador 1
    trecho[1] = setInstruction(1, 0, -1, 5); // passa valor do registrador 1 (x1) para a ram[0]
    trecho[2] = setInstruction(-1, -1, -1, -1); // haut
    
    setPrograma(cpu, trecho, 3); // envia as instruções para a cpu
    iniciar(cpu, ram); // executa as instruções na cpu
    destroiPrograma(cpu, 3); // free no programa criado   

    // calculo de x2
    int x2 = programaDiv(cpu, (-b - programaRaizAproximada(cpu, delta) ), programaMulti(cpu, 2, a)); 
    
    trecho[0] = setInstruction(1, x2, -1, 4); // envia res para o registrador 1
    trecho[1] = setInstruction(1, 1, -1, 5); // passa valor do registrador 2 (x2) para a ram[1]
    trecho[2] = setInstruction(-1, -1, -1, -1); // halt

    setPrograma(cpu, trecho, 3); // envia as instruções para a cpu
    iniciar(cpu, ram); // executa as instruções na cpu
    destroiPrograma(cpu, 3); // free no programa criado   

    // libera memorias alocadas
    trecho = destroiTrecho(trecho, 3);
    liberarRAM(ram);

    // atualiza vetor de resultados
    res[0] = x1;
    res[1] = x2;
    
    return 1;
  }
}

int programaExponencial(CPU *cpu, int base, int expoente){
  int resultado, tempMult;

  RAM *ram = criarRAM_vazia(2);
  Instruction **trecho1 = (Instruction **) malloc(5 * sizeof(Instruction*));
  trecho1[0] = setInstruction(1, 1, -1, 4);
  trecho1[1] = setInstruction(1, 0, -1, 5);
  trecho1[2] = setInstruction(2, base, -1, 4);
  trecho1[3] = setInstruction(2, 1, -1, 5);
  trecho1[4] = setInstruction(-1, -1, -1, -1);

  setPrograma(cpu, trecho1, 5);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 5);

  trecho1 = destroiTrecho(trecho1, 5);

  Instruction **trecho2 = (Instruction **) malloc(3 * sizeof(Instruction*));
  for(int i = 0; i < expoente; i++){
    tempMult = programaMulti(cpu, getDado(0, ram), getDado(1, ram));
    trecho2[0] = setInstruction(1, tempMult, -1, 4);
    trecho2[1] = setInstruction(1, 0, -1, 5);
    trecho2[2] = setInstruction(-1, -1, -1, -1);

    setPrograma(cpu, trecho2, 3);
    iniciar(cpu, ram);
    destroiPrograma(cpu, 3);
  }

  trecho2 = destroiTrecho(trecho2, 3);

  resultado = getDado(0, ram);
  ram = liberarRAM(ram);

  return resultado;
  
}

int programaLog(CPU *cpu, int base, int logaritmando){
  RAM *ram = criarRAM_vazia(1);

  Instruction **trecho = (Instruction **) malloc(3 * sizeof(Instruction *));

  int aux = 0;
  int i = 0;

  while(aux <= logaritmando){
    aux = programaExponencial(cpu, base, i);

    trecho[0] = setInstruction(1, aux, -1, 4); // envia aux para o registrador 1
    trecho[1] = setInstruction(1, 0, -1, 5); // passa valor do registrador 1 (aux) para a ram[0]
    trecho[2] = setInstruction(-1, -1, -1, -1); // halt

    setPrograma(cpu, trecho, 3);
    iniciar(cpu, ram);
    destroiPrograma(cpu, 3);

    i++;

  }

  trecho = destroiTrecho(trecho, 3);
  ram = liberarRAM(ram);

  return i-2;
}

int programaRaizCubicaAroximada(CPU *cpu, int valor) {
  RAM *ram = criarRAM_vazia(1);

  Instruction **trecho = (Instruction **) malloc(3 * sizeof(Instruction*));
  int aux = 0;
  int i = 1;

  while (aux <= valor) {
    aux = programaExponencial(cpu, i, 3);

    trecho[0] = setInstruction(1, aux, -1, 4); // reg1 recebe aux; reg1 = aux
    trecho[1] = setInstruction(1, 0, -1, 5); // ram[0] recebe o valor do reg1
    trecho[2] = setInstruction(-1, -1, -1, -1); // halt

    setPrograma(cpu, trecho, 3);
    iniciar(cpu, ram);
    destroiPrograma(cpu, 3);

    i++;
  }

  trecho = destroiTrecho(trecho, 3);
  ram = liberarRAM(ram);

  return i - 2;
}

// formula pa: an = a1 + (n - 1) * r 
int programaTermoPA(CPU *cpu, int a1, int n, int r) { // calcula o n-esimo termo
  RAM *ram = criarRAM_vazia(4);
  Instruction **trecho = (Instruction **)malloc(6 * sizeof(Instruction *));

  trecho[0] = setInstruction(1, n, -1, 4); // reg1 <- n
  trecho[1] = setInstruction(1, 0, -1, 5); // ram[0] <- reg1
  trecho[2] = setInstruction(2, 1, -1, 4); // reg2 <- 1;
  trecho[3] = setInstruction(2, 1, -1, 5); // ram[1] recebe reg2
  trecho[4] = setInstruction(0, 1, 0, 1);  // salva o resultado de n - 1 na ram[0];
  trecho[5] = setInstruction(-1, -1, -1, -1); // halt

  setPrograma(cpu, trecho, 6);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 6);

  trecho = destroiTrecho(trecho, 6);

  Instruction **trecho2 = (Instruction **) malloc(3 * sizeof(Instruction *));
  trecho2[0] = setInstruction(1, r, -1, 4); // reg1 <- r
  trecho2[1] = setInstruction(1, 1, -1, 5); // ram[1] recebe reg1
  trecho2[2] = setInstruction(-1, -1, -1, -1);

  setPrograma(cpu, trecho2, 3);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 3);

  trecho2 = destroiTrecho(trecho2, 3);

  int aux = programaMulti(cpu, getDado(0, ram), getDado(1, ram));

  Instruction **trecho3 = (Instruction **)malloc(6 * sizeof(Instruction *));
  trecho3[0] = setInstruction(1, a1, -1, 4); // reg1 <- a1
  trecho3[1] = setInstruction(1, 0, -1, 5);  // ram[0] recebe reg1;
  trecho3[2] = setInstruction(2, aux, -1, 4); // reg2 recebe aux;
  trecho3[3] = setInstruction(2, 1, -1, 5);   // ram[1] recebe reg2;
  trecho3[4] = setInstruction(0, 1, 2, 0);
  trecho3[5] = setInstruction(-1, -1, -1, -1);

  setPrograma(cpu, trecho3, 6);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 6);
  trecho3 = destroiTrecho(trecho3, 6);

  int result = getDado(2, ram);

  ram = liberarRAM(ram);
  return result;
}

RAM *programaFibonacci(CPU *cpu, RAM *ram, int n){
  if (n < 1) {
    printf("\nValor inválido!\n");

    return ram;
  }

  
  ram = aumentarRam(ram, n);

  if(n == 1) {
    Instruction **trecho = (Instruction **) malloc(3 * sizeof(Instruction*));
    trecho[0] = setInstruction(1, 0, -1, 4);
    trecho[1] = setInstruction(1, 0, -1, 5);
    trecho[2] = setInstruction(-1, -1, -1, -1);

    setPrograma(cpu, trecho, 3);
    iniciar(cpu, ram);
    destroiPrograma(cpu, 3);

    trecho = destroiTrecho(trecho, 3);

    return ram;
  }

  Instruction **trecho1 = (Instruction **) malloc(5 * sizeof(Instruction*));

  trecho1[0] = setInstruction(1, 0, -1, 4);
  trecho1[1] = setInstruction(2, 1, -1, 4);
  trecho1[2] = setInstruction(1, 0, -1, 5);
  trecho1[3] = setInstruction(2, 1, -1, 5);
  trecho1[4] = setInstruction(-1, -1, -1, -1);

  setPrograma(cpu, trecho1, 5);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 5); 

  trecho1 = destroiTrecho(trecho1, 5);

  Instruction **trecho2 = (Instruction **) malloc(2 * sizeof(Instruction*));

  for (int i = 2; i < n; i++) {
    trecho2[0] = setInstruction(i-1, i-2, i, 0);
    trecho2[1] = setInstruction(-1, -1, -1, -1);

    setPrograma(cpu, trecho2, 2); // envia as instruções para a cpu
    iniciar(cpu, ram); // executa as instruções na cpu
    destroiPrograma(cpu, 2); // free no programa criado 
  }

  trecho2 = destroiTrecho(trecho2, 2);

  return ram;

}

int programaSomaTermosPA(CPU* cpu, int a1, int n, int r) {
  RAM *ram = criarRAM_vazia(3);
  int an = programaTermoPA(cpu, a1, n, r);

  Instruction **trecho1 = (Instruction **) malloc(6 * sizeof(Instruction *));
  trecho1[0] = setInstruction(1, an, -1, 4); // reg1 <- an
  trecho1[1] = setInstruction(1, 0, -1, 5); // ram[0] <- reg1
  trecho1[2] = setInstruction(2, a1, -1, 4); // reg2 <- a1
  trecho1[3] = setInstruction(2, 1, -1, 5); // ram[1] <- reg2
  trecho1[4] = setInstruction(0, 1, 0, 0); // soma de an + a1 salva na ram[0]
  trecho1[5] = setInstruction(-1, -1, -1, -1);

  setPrograma(cpu, trecho1, 6);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 6);

  trecho1 = destroiTrecho(trecho1, 6);

  Instruction **trecho2 = (Instruction **) malloc(3 * sizeof(Instruction *));
  trecho2[0] = setInstruction(1, n, -1, 4); // reg1 <- n
  trecho2[1] = setInstruction(1, 1, -1, 5); // ram[1] <- reg1
  trecho2[2] = setInstruction(-1, -1, -1, -1);

  setPrograma(cpu, trecho2, 3);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 3);

  trecho2 = destroiTrecho(trecho2, 3);

  int temp = programaMulti(cpu, getDado(0, ram), getDado(1, ram)); // (a1 + an) x n

  Instruction **trecho3 = (Instruction **)malloc(5 * sizeof(Instruction *));
  trecho3[0] = setInstruction(1, temp, -1, 4); // reg1 <- temp
  trecho3[1] = setInstruction(1, 0, -1, 5); // ram[0] <- reg1
  trecho3[2] = setInstruction(2, 2, -1, 4); // reg2 <- 2
  trecho3[3] = setInstruction(2, 1, -1, 5); // ram[1] <- reg2
  trecho3[4] = setInstruction(-1, -1, -1, -1);

  setPrograma(cpu, trecho3, 5);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 5);

  trecho3 = destroiTrecho(trecho3, 5);

  int result = programaDiv(cpu, getDado(0, ram), getDado(1, ram));
  return result;
}