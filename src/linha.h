#ifndef LINHA_H
#define LINHA_H
#include "ponto.h"
#include <stdio.h>

//programa para linhas.

typedef void* Linha;

Linha criaLinha(Ponto p1, Ponto p2, char cor[], int id);
//cria a linha com suas informações

void printLinha(Linha l, FILE *arq);
//imprime informações da linha

Linha movelinha(Linha r, double xdisp, double ydisp, double dx, double dy);
//move a linha para uma nova posição

double getAreaLinha(Linha l);
//retorna a área da linha 

double getX1Linha(Linha l);
//retorna a coordenada x do ponto 1 da linha

double getY1Linha(Linha l);
//retorna a coordenada y do ponto 1 da linha

double getX2Linha(Linha l);
//retorna a coordenada x do ponto 2 da linha

double getY2Linha(Linha l); 
//retorna a coordenada y do ponto 2 da linha

char* getCorLinha(Linha l);
//retorna a cor da linha

void setCorLinha(Linha l, char cor[]);
//altera a cor da linha

Linha cloneLinha(Linha l, int novo_id);

void escreveLinhaTxt(Linha l, FILE *arq);

#endif