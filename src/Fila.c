#include <stdio.h>
#include <stdlib.h>
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

Item remover(Fila *f, int *tipo) {
    sNoItem **inicio = (sNoItem **)f;

    if (*inicio == NULL) { // Evita remover de fila vazia
        printf("Fila vazia!\n");
        return NULL;
    }

    sNoItem *atual = *inicio;
    sNoItem *anterior = NULL;

    // Percorre até o último nó
    while (atual->prox != NULL) {
        anterior = atual;
        atual = atual->prox;
    }

    // Se só havia um elemento
    if (anterior == NULL) {
        *inicio = NULL; // fila agora fica vazia
    } else {
        anterior->prox = NULL; // o penúltimo vira o último
    }

    Item removido = atual->item;
    *tipo = atual->tipo;
    free(atual); // desaloca o nó removido
    return removido;
}

void exibirfila(Fila f, FILE *arqnovo){
    sNoItem *atual= (sNoItem *)f;
    while(atual!=NULL){
        if (atual->tipo==1) {
            printf("\n\nCirculo:\n");
            printCirculo(atual->item, arqnovo);
        }
        else if (atual->tipo==2) {
            printf("\n\nRetangulo:\n");
            printRetangulo(atual->item, arqnovo);
        }
        else if (atual->tipo==3) {
            printf("\n\nLinha:\n");
            printLinha(atual->item, arqnovo);
        }
        else if (atual->tipo==4) {
            printf("\n\nTexto:\n");
            printTexto(atual->item, arqnovo);
        }
        atual=atual->prox;
    }
    printf("\n");
}

Fila criafila(){
    return NULL;
}

int filavazia(Fila f) {
    sNoItem *atual= (sNoItem *)f;
    if(atual==NULL){
        return 1;
    }
    return 0;
}