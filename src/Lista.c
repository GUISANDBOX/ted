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
}


Disparador buscadisparador(Lista l, int id) {
    printf("Inicio de buscadisparador\n");
    sNoDisp *atual= (sNoDisp *)l;
    while(atual!=NULL){
        atual=atual->prox;
    }
    printf("\n");
    return NULL;
}

Item removernalista(Lista *l, Item item){
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
    return removido;
}

void exibirlista(Lista l){
    sNoDisp *atual= (sNoDisp *)l;
    while(atual!=NULL){

        atual=atual->prox;
    }
    printf("\n");
}

Lista crialista(){
    return NULL;
}
