#include "Pilha.h"
#include "disparador.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include <stdlib.h>
#include <stdio.h>

struct sDisparador {
    int id;
    double x;
    double y;
    Item disparo;
    int tipo;
    Pilha esq;
    Pilha dir;
};

Disparador criaDisparador(int id, double x, double y) {
    struct sDisparador *d = malloc(sizeof(struct sDisparador));
    if(!d){
        printf("Erro na alocação do disparador\n");
        return NULL;
    }
    d->id = id;
    d->x = x;
    d->y = y;
    d->disparo = NULL;
    d->tipo = 0;
    d->esq = NULL;
    d->dir = NULL;
    return (Disparador)d;
}

void encaixar(Disparador d, Pilha esq, Pilha dir) {
    struct sDisparador *disp = (struct sDisparador *)d;
    disp->esq = esq;
    disp->dir = dir;
}

Pilha botao(Disparador d, char lado) {
    if (d == NULL) {
        printf("botao: disparador nulo\n");
        return NULL;
    }
    printf("Apertando o botao %c do disparador\n", lado);
    imprimedisparador(d);
    tipoatualnodisparo(d);
    struct sDisparador *disp = d;
    printf("Estado antes do tipo: ");
    int tipo=0;
    printf("Estado antes do botao: ");
    if (lado=='e') {
        printf("BOTAO E no disparador %d; ", disp->id);
        if(disp->disparo==NULL){
            printf("Posição de disparo vazio\n");
            Item obj = desempilha(&(disp->dir), &tipo);
            if (obj == NULL) {
                printf("erro ao desempilhar %d\n", disp->id);
                return NULL;
            }
            disp->disparo = obj;
            disp->tipo = tipo;
            return disp->dir;
        }
        else{
            empilha(&(disp->esq), disp->disparo, tipo);
            Item obj = desempilha(&(disp->dir), &tipo);
            if (obj == NULL) {
                printf("erro ao desempilhar %d\n", disp->id);
                return NULL;
            }
            disp->disparo = obj;
            disp->tipo = tipo;
            return disp->dir;
        }
    }
    else {
        printf("BOTAO D no disparador %d; ", disp->id);
        if(disp->disparo==NULL){
            printf("Posição de disparo vazio\n");
            Item obj = desempilha(&(disp->esq), &tipo);
            if (obj == NULL) {
                printf("erro ao desempilhar %d\n", disp->id);
                return NULL;
            }
            disp->disparo = obj;
            disp->tipo = tipo;
            return disp->esq;
        }
        else{
            empilha(&(disp->dir), disp->disparo, tipo);
            Item obj = desempilha(&(disp->esq), &tipo);
            if (obj == NULL) {
                printf("erro ao desempilhar %d\n", disp->id);
                return NULL;
            }
            disp->disparo = obj;
            disp->tipo = tipo;
            return disp->esq;
        }
    }
}

Item disparar(Disparador d, double dx, double dy) {
    struct sDisparador *disp = (struct sDisparador *)d;
    Item itemdisparo;
    if (disp->tipo==1) { // Circulo
        itemdisparo = movecirculo(disp->disparo, disp->x, disp->y, dx, dy);
    }
    else if (disp->tipo==2) {
        itemdisparo = moveretangulo(disp->disparo, disp->x, disp->y, dx, dy);
    }
    else if (disp->tipo==3) {
        itemdisparo = movelinha(disp->disparo, disp->x, disp->y, dx, dy);
    }
    else if (disp->tipo==4) {
        itemdisparo = movetexto(disp->disparo, disp->x, disp->y, dx, dy);
    }
    disp->disparo = NULL;
    return itemdisparo;
}

int iddisparador(Disparador d) {
    struct sDisparador *disp = (struct sDisparador *)d;
    return disp->id;
}

int tipoatualnodisparo(Disparador d) {
    struct sDisparador *disp = (struct sDisparador *)d;
    printf("Tipo atual no disparo: %d\n", disp->tipo);
    return disp->tipo;
}

void imprimedisparador(Disparador d) {
    struct sDisparador *disp = (struct sDisparador *)d;
    printf("Disparador %d em (%lf, %lf)\n", disp->id, disp->x, disp->y);
}

Pilha getPilhaEsq(Disparador d) {
    struct sDisparador *disp = (struct sDisparador *)d;
    return disp->esq;
}

Pilha getPilhaDir(Disparador d) {
    struct sDisparador *disp = (struct sDisparador *)d;
    return disp->dir;
}