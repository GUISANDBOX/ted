#include "Pilha.h"
#include "disparador.h"
#include "circulo.h"
#include "retangulo.h"
#include<stdlib.h>
#include<stdio.h>

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
    d->id = id;
    d->x = x;
    d->y = y;
    d->disparo = NULL;
    return (Disparador)d;
}

void encaixar(Disparador d, Pilha esq, Pilha dir) {
    struct sDisparador *disp = (struct sDisparador *)d;
    disp->esq = esq;
    disp->dir = dir;
}

void botao(Disparador d, char lado) {
    // Botão esquerdo
    struct sDisparador *disp = (struct sDisparador *)d;
    int tipo;
    if (lado=='e') {
        printf("BOTAO E no disparador %d; ", disp->id);
        exibir(disp->esq);
        Item obj = desempilha(&(disp->esq), &tipo);
         printf("POP FEITO de um %d ", tipo);
        if (disp->disparo!=NULL) { // Está vazio inicialmente
            empilha(disp->dir, disp->disparo, tipo);
        }
        disp->disparo = obj;
        disp->tipo = tipo;
    }
    // TODO implementar a lógica do 'd'
}

Item disparar(Disparador d, double dx, double dy) {
    struct sDisparador *disp = (struct sDisparador *)d;
    Item itemdisparo;
    if (disp->tipo==0) { // Circuulo

    }
    else if (disp->tipo==1) {
        itemdisparo = moveretangulo(disp->disparo, disp->x, disp->y, dx, dy);
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
    return disp->tipo;
}

void imprimedisparador(Disparador d) {
    struct sDisparador *disp = (struct sDisparador *)d;
    printf("Disparador %d em (%lf, %lf)\n", disp->id, disp->x, disp->y);
}