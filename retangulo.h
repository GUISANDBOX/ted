#ifndef RET_H
#define RET_H
#include<stdio.h>

typedef void *Retangulo;

Retangulo criaRetangulo(double x, double y, double w, double h, char corb[100], char corp[100], int id);

void printRetangulo(Retangulo r, FILE *arq);

Retangulo moveretangulo(Retangulo r, double xdisp, double ydisp, double dx, double dy);

#endif