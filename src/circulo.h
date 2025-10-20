#ifndef CIRCULO_H
#define CIRCULO_H
#include "ponto.h"
#include <stdio.h>

//programa para circulos

typedef void* Circulo;

Circulo criaCirculo(Ponto centro, float raio, char corb[], char corp[], int id);
//cria um circulo com suas informações

void printCirculo(Circulo c, FILE *arq);
//imprime informações do circulo

#endif