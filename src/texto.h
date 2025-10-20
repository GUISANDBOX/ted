#ifndef TEXTO_H
#define TEXTO_H
#include "ponto.h"
#include <stdio.h>

//programa para textos.

typedef void* Texto;

Texto criaTexto(Ponto ponto, char corb[100], char corp[100], char txto[100], char a, char currentFFamily[10], char currentFWeight[10], char currentFSize[10], int id) ;
//cria o texto com suas informações

void printTexto(Texto t, FILE *arq);
//imprime informações do texto

Texto movetexto(Texto r, double xdisp, double ydisp, double dx, double dy);
//move o texto para uma nova posição

#endif