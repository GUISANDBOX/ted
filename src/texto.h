#ifndef TEXTO_H
#define TEXTO_H
#include "ponto.h"
#include <stdio.h>

//programa para textos.

typedef void* Texto;

Texto criaTexto(Ponto ponto, char corb[], char corp[], char txto[], char a, char currentFFamily[], char currentFWeight[], char currentFSize[], int id) ;
//cria o texto com suas informações

void printTexto(Texto t, FILE *arq);
//imprime informações do texto

Texto movetexto(Texto r, double xdisp, double ydisp, double dx, double dy);
//move o texto para uma nova posição

#endif