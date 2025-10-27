#ifndef RET_H
#define RET_H
#include<stdio.h>

//programa para retângulos.

typedef void *Retangulo;

Retangulo criaRetangulo(double x, double y, double w, double h, char corb[100], char corp[100], int id);
//cria o retângulo com suas informações

void printRetangulo(Retangulo r, FILE *arq);
//imprime as informações do retângulo

Retangulo moveretangulo(Retangulo r, double xdisp, double ydisp, double dx, double dy);
//move o retângulo para uma nova posição

double areaRetangulo(Retangulo r);
//calcula a área do retângulo

#endif