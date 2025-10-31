#ifndef QRY_H
#define QRY_H

#include <stdio.h>
#include "Fila.h"
#include "Pilha.h"
#include "disparador.h"
#include "retangulo.h"
#include "circulo.h"
#include "linha.h"
#include "texto.h"
#include <math.h>


void processaQry(FILE *fileq, Fila filasaida, FILE *filesaidaquery, Fila filaOriginal, FILE *arqtxt);
//processa os comandos do arquivo .qry

int retangulosSobrepoem(Retangulo r1, Retangulo r2);

int circulosSobrepoem(Circulo c1, Circulo c2);

int circuloRetanguloSobrepoem(Circulo c, Retangulo r);

Fila executaCalc(Fila filasaida, Fila filaOriginal, FILE *filesaidaquery);

int linhasSobrepoem(Item l1, Item l2, int tipo1, int tipo2);


int linhaOuTexto(int tipo);

Ponto getP1Item(Item item, int tipo);


Ponto getP2Item(Item item, int tipo);

double areaLinha(Item item, int tipo);

char *getCorbLinha(Item item, int tipo);


char *getCorpLinha(Item item, int tipo);


#endif