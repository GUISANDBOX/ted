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

#endif