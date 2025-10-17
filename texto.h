#ifndef TEXTO_H
#define TEXTO_H

#include "ponto.h"
#include <stdio.h>

typedef void* Texto;

Texto criaTexto(Ponto ponto, char corb[100], char corp[100], char txto[100], char a, int id) ;

void printTexto(Texto t, FILE *arq);

#endif