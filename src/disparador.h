#ifndef DISP_H
#define DISP_H
#include "Pilha.h"

//programa com funções relacionadas ao disparador.

typedef void* Disparador;

Disparador criaDisparador(int id, double x, double y);
//cria o disparador

void encaixar(Disparador d, Pilha esq, Pilha dir);
//coloca os carregadores no disparador

Pilha botao(Disparador d, char lado);
//aperta o botão de um dos lados

Item disparar(Disparador d, double dx, double dy);
//dispara o objeto a uma distância adicional do disparador

int iddisparador(Disparador d);
//retorna o id do disparador

void imprimedisparador(Disparador d);
//imprime instruções do disparador

int tipoatualnodisparo(Disparador d);
//mostra o tipo na posição de disparo

Pilha getPilhaEsq(Disparador d);
//retorna a pilha esquerda do disparador

Pilha getPilhaDir(Disparador d);
//retorna a pilha direita do disparador

Item itemAtualNoDisparo(Disparador d);
//retorna o item atual na posição de disparo

#endif