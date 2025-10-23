#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

struct elemento{
    Item item;
    int tipo; // 1 - circulo, 2 - retangulo, 3 - linha, 4 - texto
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
    if(atual==NULL){
        printf("Pilha vazia!\n");
        return;
    }
    while(atual!=NULL){
        if (atual->tipo==1) {
            printCirculo(atual->item, NULL);
        }
        if (atual->tipo==2) {
            printRetangulo(atual->item, NULL);
        }
        if (atual->tipo==3) {
            printLinha(atual->item, NULL);
        }
        if (atual->tipo==4) {
            printTexto(atual->item, NULL);
        }
        atual=atual->prox;
    }
    printf("\n");
}

int pilhavazia(Pilha p){
    sNoItem *topo= (sNoItem *)p;
    if (topo==NULL) {
        return 1; // Vazia
    }
    return 0; // Nao vazia
}

Pilha criapilha(){
    return NULL;
}