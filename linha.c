#include "linha.h"
#include "ponto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Criasvg.h"

struct sLinha {
    int id;
    Ponto p1;
    Ponto p2;
    char cor[100];
};

Linha criaLinha(Ponto p1, Ponto p2, char cor[100], int id) {
    struct sLinha *l = malloc(sizeof(struct sLinha));
    if (!l) return NULL; // segurança
    l->p1 = p1;
    l->p2 = p2;
    l->id = id;
    strcpy(l->cor, cor); // Cor
    return (Linha)l;
}

void printLinha(Linha l, FILE *arq) {
    struct sLinha *lin = l;
    printf("\n\nID: %i\n", lin->id);
    printf("P1: (%f, %f)\n", getX(lin->p1), getY(lin->p1));
    printf("P2: (%f, %f)\n", getX(lin->p2), getY(lin->p2));
    printf("Cor: %s \n", lin->cor);
    crialinha(lin->id, getX(lin->p1), getY(lin->p1), getX(lin->p2), getY(lin->p2), lin->cor, arq);
}