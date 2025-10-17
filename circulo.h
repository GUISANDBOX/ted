#ifndef CIRCULO_H
#define CIRCULO_H

#include "ponto.h"
#include<stdio.h>

typedef void* Circulo;

Circulo criaCirculo(Ponto centro, float raio, char corb[], char corp[], int id);

void printCirculo(Circulo c, FILE *arq);

#endif