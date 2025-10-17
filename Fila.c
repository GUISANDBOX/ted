#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "Fila.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

struct elemento{
    Item item;
    int tipo; // 0 - circulo, 1 retangulo, etc
    struct elemento *prox;
};

typedef struct elemento sNoItem;

void adicionar(Fila *f,  Item item, int tipo){
    sNoItem **inicio = (sNoItem **)f;
    sNoItem *novo=(sNoItem *)malloc(sizeof(sNoItem));
    if(!novo){
        printf("Erro na alocação\n");
        return;
    }
    novo->item=item;
    novo->tipo = tipo;
    novo->prox = *inicio; // Aponta o prox para o topo atual
    *inicio = novo;
}

Item remover(Fila *f, int *tipo){
    sNoItem **inicio = (sNoItem **)f;
    if (*inicio==NULL) { // Evita remover de fila vazia
        printf("Fila vazia!\n");
        return NULL;
    }

    sNoItem *old = *inicio;
    sNoItem *antes = *inicio;
    old = old->prox;
    while (old->prox != NULL) {
        antes = antes->prox;
        old = old->prox;
    }
    Item removido = old->item;
    antes->prox = NULL; // Atualiza o novo fim
    *tipo = old->tipo;
    //free(old); // Desaloca da mem�ria o item removido
    return removido;
}

void exibirfila(Fila f, FILE *arqnovo){
    sNoItem *atual= (sNoItem *)f;
    while(atual!=NULL){
        if (atual->tipo==0) {
            printCirculo(atual->item, arqnovo);
        }
        else if (atual->tipo==1) {
            printRetangulo(atual->item, arqnovo);
        }
        else if (atual->tipo==2) {
            printLinha(atual->item, arqnovo);
        }
        else if (atual->tipo==3) {
            printTexto(atual->item, arqnovo);
        }
        atual=atual->prox;
    }
    printf("\n");
}

Fila criafila(int quantidade,...){
    if (quantidade==0) return NULL;
}

void liberarfila(Fila f){
    /*struct elemento *atual=f->inicio;
    struct elemento *prox;
    while(atual!=NULL){
        prox=atual->prox;
        free(atual);
        atual=prox;
    }
    free(f);*/
}