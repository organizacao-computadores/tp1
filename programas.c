#include <stdio.h>
#include <stdlib.h>

#include "programas.h"

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
