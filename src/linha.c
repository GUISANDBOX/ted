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

Linha movelinha(Linha l, double xdisp, double ydisp, double dx, double dy) {
    struct sLinha *lin = l;
    double nx = xdisp + dx;
    double ny = ydisp + dy;

    double x1 = getX(lin->p1);
    double y1 = getY(lin->p1);
    double x2 = getX(lin->p2);
    double y2 = getY(lin->p2);

    double deltaX, deltaY;
    Ponto novoMenor, novoOutro;

    if (x1 < x2 || (x1 == x2 && y1 <= y2)) {
        /* p1 é o menor */
        deltaX = x2 - x1;
        deltaY = y2 - y1;
        novoMenor = criaPonto(nx, ny);
        novoOutro = criaPonto(nx + deltaX, ny + deltaY);
        lin->p1 = novoMenor;
        lin->p2 = novoOutro;
    }
    else {
        /* p2 é o menor */
        deltaX = x1 - x2;
        deltaY = y1 - y2;
        novoMenor = criaPonto(nx, ny);
        novoOutro = criaPonto(nx + deltaX, ny + deltaY);
        lin->p2 = novoMenor;
        lin->p1 = novoOutro;
    }   
    return lin;
}

void printLinha(Linha l, FILE *arq) {
    struct sLinha *lin = l;
    printf("\n\nID: %i\n", lin->id);
    printf("P1: (%f, %f)\n", getX(lin->p1), getY(lin->p1));
    printf("P2: (%f, %f)\n", getX(lin->p2), getY(lin->p2));
    printf("Cor: %s \n", lin->cor);
    crialinha(lin->id, getX(lin->p1), getY(lin->p1), getX(lin->p2), getY(lin->p2), lin->cor, arq);
}