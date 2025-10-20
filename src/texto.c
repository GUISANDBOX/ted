#include "texto.h"
#include "ponto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Criasvg.h"

struct sTexto {
    int id;
    Ponto ponto;
    char corb[100];
    char corp[100];
    char txto[100];
    char ancora;
    char currentFFamily[10];
    char currentFWeight[10];
    char currentFSize[10];
};

Texto criaTexto(Ponto ponto, char corb[100], char corp[100], char txto[100], char a, char currentFFamily[10], char currentFWeight[10], char currentFSize[10], int id) {
    struct sTexto *t = malloc(sizeof(struct sTexto));
    if (!t) return NULL; // segurança
    t->ponto = ponto;
    t->id = id;
    t->ancora = a;
    strcpy(t->corb, corb); // Cor da borda
    strcpy(t->corp, corp); // Cor de preenchimento
    strcpy(t->txto, txto); // Texto
    strcpy(t->currentFFamily, currentFFamily);
    strcpy(t->currentFWeight, currentFWeight);
    strcpy(t->currentFSize, currentFSize);
    return (Texto)t;
}

Texto movetexto(Texto t, double xdisp, double ydisp, double dx, double dy) {
    struct sTexto *tex = t;
    double nx = xdisp + dx;
    double ny = ydisp + dy;
    Ponto novo = criaPonto(nx, ny);
    tex->ponto = novo;
    return tex;
}

void printTexto(Texto t, FILE *arq) {
    struct sTexto *tex = t;
    printf("\n\nID: %i\n", tex->id);
    printf("Âncora: (%f, %f)\n", getX(tex->ponto), getY(tex->ponto));
    printf("Cores borda/preenchimento: %s/%s \n", tex->corb, tex->corp);
    printf("Texto: %s \n", tex->txto);
    printf("Família/Peso/Tamanho: %s/%s/%s \n", tex->currentFFamily, tex->currentFWeight, tex->currentFSize);
    criatexto(tex->id, getX(tex->ponto), getY(tex->ponto), tex->corb, tex->corp, tex->ancora, tex->txto, tex->currentFFamily, tex->currentFWeight, tex->currentFSize, arq);
}