#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
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
    // if(p->topo==NULL){
    //     p->topo=novo;
    //     novo->prox=NULL;
    // }
    // else{
    //     novo->prox=p->topo;
    //     p->topo=novo;
    // }
}

Item desempilha(Pilha *p, int *tipo){
    // if(p->topo==NULL){
    //     printf("A pilha está vazia\n");
    //     return;
    // }
    // struct elemento *atual=p->topo;
    // p->topo=atual->prox;
    // free(atual);
    sNoItem **topo = (sNoItem **)p;
    if (*topo==NULL) { // Evita remover de pilha vazia
        printf("Pilha vazia!\n");
        return NULL;
    }

    sNoItem *old = *topo;
    Item removido = old->item;
    *tipo = old->tipo;
    *topo = (*topo)->prox; // Atualiza o novo topo
    //free(old); // Desaloca da mem�ria o item removido
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

Pilha criapilha(int quantidade,...){
    if (quantidade==0) return NULL;
    /*struct pilha *p=malloc(sizeof(struct pilha));
    if(!p){
        printf("Erro na alocação\n");
        return NULL;
    }
    inicializa(p);
    va_list argumentos;
    va_start(argumentos,quantidade);
    for(int i=0;i<quantidade;i++){
        double elemento=va_arg(argumentos,double);
        empilha(p,elemento);
    }
    va_end(argumentos);
    return p;*/
}

void liberarpilha(Pilha p){
    /*struct elemento *atual=p->topo;
    struct elemento *prox;
    while(atual!=NULL){
        prox=atual->prox;
        free(atual);
        atual=prox;
    }
    free(p);*/
}