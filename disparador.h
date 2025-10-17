#ifndef DISP_H
#define DISP_H
#include "Pilha.h"

typedef void* Disparador;

Disparador criaDisparador(int id, double x, double y);

void encaixar(Disparador d, Pilha esq, Pilha dir);

void botao(Disparador d, char lado);

Item disparar(Disparador d, double dx, double dy);

int iddisparador(Disparador d);

void imprimedisparador(Disparador d);

int tipoatualnodisparo(Disparador d);

#endif