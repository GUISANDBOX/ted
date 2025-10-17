#ifndef LINHA_H
#define LINHA_H

#include "ponto.h"
#include <stdio.h>

typedef void* Linha;

Linha criaLinha(Ponto p1, Ponto p2, char cor[], int id);

void printLinha(Linha l, FILE *arq);

#endif