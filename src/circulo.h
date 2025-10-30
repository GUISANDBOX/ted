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

Circulo movecirculo(Circulo r, double xdisp, double ydisp, double dx, double dy);
//move o circulo para uma nova posição

double areaCirculo(Circulo c);
//calcula a área do círculo

double getXCirculo(Circulo c);
//retorna a coordenada x do círculo

double getYCirculo(Circulo c);
//retorna a coordenada y do círculo

double getRCirculo(Circulo c);
//retorna o raio do círculo

void setCorbCirculo(Circulo c, char corb[100]);
//altera a cor da borda do círculo

Circulo clonecirculo(Circulo c, int novo_id);

int getIdCirculo(Circulo c); 

char* getCorbCirculo(Circulo c);
//retorna a cor de borda do círculo

char* getCorpCirculo(Circulo c);
//retorna a cor de preenchimento do círculo

void setCorpCirculo(Circulo c, char corp[100]);
//altera a cor de preenchimento do círculo

void escreveCirculoTxt(Circulo c, FILE *arq);

#endif