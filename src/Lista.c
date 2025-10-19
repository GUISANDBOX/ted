#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"
#include "disparador.h"

struct elementod{
    Disparador item;
    struct elementod *prox;
};

typedef struct elementod sNoDisp;

void adicionarnalista(Lista *l,  Disparador item){
    sNoDisp **inicio = (sNoDisp **)l;
    sNoDisp *novo=(sNoDisp *)malloc(sizeof(sNoDisp));
    if(!novo){
        printf("Erro na alocação\n");
        return;
    }
    novo->item=item;
    novo->prox = *inicio; // Aponta o prox para o topo atual
    *inicio = novo;
    printf("Inserido o disparador ");
    imprimedisparador(novo->item);
    // if(l->inicio==NULL){
    //     l->inicio=novo;
    //     novo->prox=NULL;
    // }
    // else{
    //     novo->prox=l->inicio;
    //     l->inicio=novo;
    // }
}


Disparador buscadisparador(Lista l, int id) {
    printf("Inicio de buscadisparador\n");
    sNoDisp *atual= (sNoDisp *)l;
    while(atual!=NULL){
        //imprimedisparador(atual->item);
        atual=atual->prox;
    }
    printf("\n");
    return NULL;
}

Item removernalista(Lista *l, Item item){
    // if(l->inicio==NULL){
    //     printf("A lista está vazia\n");
    //     return;
    // }
    // struct elemento *atual=l->inicio;
    // while
    // free(atual);
    sNoDisp **inicio = (sNoDisp **)l;
    if (*inicio==NULL) { // Evita remover de lista vazia
        printf("Lista vazia!\n");
        return NULL;
    }

    sNoDisp *old = *inicio;
    sNoDisp *antes = *inicio;
    old = old->prox;
    while (old->prox != NULL && old->item != item) {
        antes = antes->prox;
        old = old->prox;
    }
    if (old->item != item && old->prox == NULL) {
        printf("Não está na lista!\n");
        return NULL;
    }
    Item removido = old->item;
    antes->prox = old->prox; // Atualiza o novo fim
    //free(old); // Desaloca da mem�ria o item removido
    return removido;
}

void exibirlista(Lista l){
    sNoDisp *atual= (sNoDisp *)l;
    while(atual!=NULL){

        atual=atual->prox;
    }
    printf("\n");
}

Lista crialista(int quantidade,...){
    if (quantidade==0) return NULL;
    /*struct lista *l=malloc(sizeof(struct lista));
    if(!l){
        printf("Erro na alocação\n");
        return NULL;
    }
    inicializa(l);
    va_list argumentos;
    va_start(argumentos,quantidade);
    for(int i=0;i<quantidade;i++){
        double elemento=va_arg(argumentos,double);
        adicionar(l,elemento);
    }
    va_end(argumentos);
    return l;*/
}

void liberarlista(Lista l){
    /*struct elemento *atual=l->inicio;
    struct elemento *prox;
    while(atual!=NULL){
        prox=atual->prox;
        free(atual);
        atual=prox;
    }
    free(l);*/
}
