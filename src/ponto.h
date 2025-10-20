#ifndef PONTO_H
#define PONTO_H

//programa para pontos.

typedef void* Ponto;

Ponto criaPonto(float x, float y);
//cria o ponto com suas informações

void printPonto(Ponto p);
//imprime as informações do ponto

float getX(Ponto p);
//retorna a coordenada x do ponto

float getY(Ponto p);
//retorna a coordenada y do ponto

#endif