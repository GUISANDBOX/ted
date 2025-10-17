#ifndef PONTO_H
#define PONTO_H

typedef void* Ponto;

Ponto criaPonto(float x, float y);

void printPonto(Ponto p);

float getX(Ponto p);

float getY(Ponto p);

#endif