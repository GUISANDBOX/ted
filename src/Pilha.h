#ifndef PILHA
#define PILHA

//programa para pilhas.
typedef void* Item; // Define que cada item da pilha é uma pilha genérica
typedef void* Pilha;

//cria a pilha com a quantidade de elementos e os elementos.
Pilha criapilha(int quantidade,...);

// Adiciona um item na Pilha
void empilha(Pilha *p, Item item, int tipo);

// Remove o elemento do topo da pilha.
Item desempilha(Pilha *p, int *tipo);

//exibe os elementos da pilha.
void exibir(Pilha p);

void liberarpilha(Pilha p);
//libera a pilha da memória.

#endif