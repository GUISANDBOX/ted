#ifndef FILA
#define FILA

//programa para filas.
typedef void* Item; // Define que cada item da fila é uma fila genérica
typedef void* Fila;

Fila criafila();
//cria a fila

void adicionar(Fila *f, Item item, int tipo);
// Adiciona um item na Fila

Item remover(Fila *f, int *tipo);
// Remove o elemento do fim da fila.

void exibirfila(Fila f, FILE *arqnovo);
//exibe os elementos da fila.

int filavazia(Fila f);
//verifica se a fila está vazia

#endif