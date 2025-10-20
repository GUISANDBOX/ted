#include "circulo.h"
#include "ponto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Criasvg.h"

struct sCirculo {
    int id;
    Ponto centro;
    float raio;
    char corb[100];
    char corp[100];
};

Circulo criaCirculo(Ponto centro, float raio, char corb[100], char corp[100], int id) {
    struct sCirculo *c = malloc(sizeof(struct sCirculo));
    if (!c) return NULL; // segurança
    c->centro = centro;
    c->raio = raio;
    c->id = id;
    strcpy(c->corb, corb); // Cor da borda
    strcpy(c->corp, corp); // Cor de preenchimento
    return (Circulo)c;
}

Circulo movecirculo(Circulo c, double xdisp, double ydisp, double dx, double dy) {
    struct sCirculo *circ = c;
    double nx = xdisp + dx;
    double ny = ydisp + dy;
    Ponto novo = criaPonto(nx, ny);
    circ->centro = novo;
    return circ;
}

void printCirculo(Circulo c, FILE *arq) {
    struct sCirculo *circ = c;
    printf("\n\nID: %i\n", circ->id);
    printf("Centro: (%f, %f)\n", getX(circ->centro), getY(circ->centro));
    printf("Raio: %.1f \n", circ->raio);
    printf("Cores borda/preenchimento: %s/%s \n", circ->corb, circ->corp);
    if (arq!=NULL) criacirculo(circ->id, getX(circ->centro), getY(circ->centro), circ->raio, circ->corb, circ->corp, arq);
}

