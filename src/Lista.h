#ifndef LISTA
#define LISTA
#include "disparador.h"

//programa para listas.
typedef void* Item; // Define que cada item da lista é uma lista genérica
typedef void* Lista;

Lista crialista(int quantidade,...);
//cria a lista com a quantidade de elementos e os elementos.

void adicionarnalista(Lista *l, Disparador item);
// Adiciona um item no inicio da lista

Item removernalista(Lista *l, Item item);
// Remove um elemento da lista.

void exibirlista(Lista l);
//exibe os elementos da lista.

void liberarlista(Lista l);
//libera a lista da memória.

Disparador buscadisparador(Lista l, int id);

#endif