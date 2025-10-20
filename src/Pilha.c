#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"
#include "circulo.h"
#include "retangulo.h"

struct elemento{
    Item item;
    int tipo; // 0 - circulo, 1 retangulo, 2 - linha, 3 - texto
    struct elemento *prox;
};

typedef struct elemento sNoItem;

void empilha(Pilha *p,  Item item, int tipo){
    sNoItem **topo = (sNoItem **)p;
    sNoItem *novo=(sNoItem *)malloc(sizeof(sNoItem));
    if(!novo){
        printf("Erro na alocação\n");
        return;
    }
    novo->item=item;
    novo->tipo = tipo;
    novo->prox = *topo; // Aponta o prox para o topo atual
    *topo = novo;
}

Item desempilha(Pilha *p, int *tipo){
    sNoItem **topo = (sNoItem **)p;
    if (*topo==NULL) { // Evita remover de pilha vazia
        printf("Pilha vazia!\n");
        return NULL;
    }

    sNoItem *old = *topo;
    Item removido = old->item;
    *tipo = old->tipo;
    *topo = (*topo)->prox; // Atualiza o novo topo

    return removido;
}

void exibir(Pilha p){
    sNoItem *atual= (sNoItem *)p;
    while(atual!=NULL){
        if (atual->tipo==0) {
            printCirculo(atual->item, NULL);
        }
        if (atual->tipo==1) {
            printRetangulo(atual->item, NULL);
        }
        // Fazer para outros...
        atual=atual->prox;
    }
    printf("\n");
}

Pilha criapilha(){
    return NULL;
}