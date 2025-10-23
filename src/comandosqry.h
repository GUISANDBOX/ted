#ifndef QRY_H
#define QRY_H

#include <stdio.h>
#include "Fila.h"
#include "Pilha.h"
#include "disparador.h"

void processaQry(FILE *fileq, Fila filasaida, FILE *filesaidaquery, Fila filaOriginal);
//processa os comandos do arquivo .qry

#endif