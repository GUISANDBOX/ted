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

#endif