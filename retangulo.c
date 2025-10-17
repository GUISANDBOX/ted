#include "retangulo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Criasvg.h"

struct sRetangulo {
    int id;
    double x;
    double y;
    double w;
    double h;
    char corb[100];
    char corp[100];
};

Retangulo criaRetangulo(double x, double y, double w, double h, char corb[100], char corp[100], int id) {
    struct sRetangulo *r = malloc(sizeof(struct sRetangulo));
    r->id = id;
    r->x = x;
    r->y = y;
    r->w = w;
    r->h = h;
    strcpy(r->corb, corb); // Cor da borda
    strcpy(r->corp, corp); // Cor de preenchimento
    return r;
}

Retangulo moveretangulo(Retangulo r, double xdisp, double ydisp, double dx, double dy) {
    struct sRetangulo *ret = r;
    ret->x = xdisp + dx;
    ret->y = ydisp + dy;
    return ret;
}

void printRetangulo(Retangulo r, FILE *arq) {
    struct sRetangulo *ret = r;
    printf("\n\nID: %i\n", ret->id);
    printf("Ancora: %lf %lf\n", ret->x, ret->y);
    printf("Largura/altura: %lf %lf\n", ret->w, ret->h);
    printf("Cores borda/preenchimento: %s/%s \n", ret->corb, ret->corp);

    if (arq!=NULL) criaretangulo(ret->id, ret->x, ret->y, ret->w, ret->h, ret->corb, ret->corp, arq);
}