#include <stdio.h>
#include <stdlib.h>

#include "programas.h"

int programaMulti(RAM *ram, CPU *cpu, int a, int b){
  int result;
  ram = criarRAM_vazia(2);
  Instruction **trecho1;
  trecho1 = (Instruction**) malloc(3 * sizeof(Instruction*));

  trecho1[0] = setInstruction(1, a, -1, 4);
  trecho1[1] = setInstruction(1, 1, -1, 2);
  trecho1[2] = setInstruction(-1, -1, -1, -1);


  setPrograma(cpu, trecho1, 3);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 3);


  destroiTrecho(trecho1, 3);

  Instruction **trecho2;
  trecho2 = (Instruction**) malloc(2 * sizeof(Instruction*));
  for(int i = 0; i < b; i++){
    trecho2[0] = setInstruction(0, 1, 0, 0);
    trecho2[1] = setInstruction(-1, -1, -1, -1);

    setPrograma(cpu, trecho2, 2);
    iniciar(cpu, ram);
    destroiPrograma(cpu, 2);
  }


  destroiTrecho(trecho2, 2);

  Instruction **trecho3;
  trecho3 = (Instruction **) malloc(3 * sizeof(Instruction*));

  trecho3[0] = setInstruction(1, 0, -1, 3);
  trecho3[1] = setInstruction(1, 2, -1, 5);
  trecho3[2] = setInstruction(-1, -1, -1, -1);


  setPrograma(cpu, trecho3, 3);
  iniciar(cpu, ram);
  destroiPrograma(cpu, 3);


  destroiTrecho(trecho3, 3);

  result = getDado(0, ram);
  ram = liberarRAM(2, ram);


  return result;
}