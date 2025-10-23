#include "comandosqry.h"
#include <string.h>
#include <stdio.h>

void processaQry(FILE *fileq, Fila filasaida, FILE *filesaidaquery, Fila filaOriginal) {
    Disparador listadisp[100];
    Pilha listacarr[100];
    char comando[32];
    int z, i, j, n, tipo;
    int iesq, idir;
    float x, y, x1, y1, x2, y2;
    char a;

    // Inicializa as pilhas
    for (j=0; j<100; j++) {
        listacarr[j] = criapilha(0);
    }

    fprintf(filesaidaquery, "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
    printf("Iniciando processamento do QRY\n");
    do {
        z = fscanf(fileq, " %31s", comando);
        if (z != 1) break;

        printf("LIDO %s\n", comando);

        if (!strcmp(comando, "pd")) {
            fscanf(fileq, "%d %f %f", &i, &x, &y);
            listadisp[i] = criaDisparador(i, x, y);
            printf("Disparador %d criado!\n", iddisparador(listadisp[i]));
        }
        else if (!strcmp(comando, "lc")) {
            fscanf(fileq, "%d %d", &i, &n);
            printf("Inicializando carregador!\n");
            Pilha pilha = criapilha(0);
            Item item;
            for (j=0; j<n; j++) {
                item = remover(&filaOriginal, &tipo);
                empilha(&pilha, item, tipo);
            }
            printf("Pilha %d carregada!\n", i);
            listacarr[i] = pilha;
        }
        else if (!strcmp(comando, "atch")) {
            fscanf(fileq, "%d %d %d", &i, &iesq, &idir);
            printf("Encaixando disparadores!\n");
            encaixar(listadisp[i], listacarr[iesq], listacarr[idir]);
            printf("Encaixe realizado!\n");
        }
        else if (!strcmp(comando, "rjd")) {
            fscanf(fileq, "%i %c %f %f %f %f", &i, &a, &x1, &y1, &x2, &y2);
            printf("REALIZANDO RAJADA\n");
            Pilha pilhadodisparador;
            
            pilhadodisparador = (a=='d') ? getPilhaEsq(listadisp[i]) : getPilhaDir(listadisp[i]);
            
            while(!pilhavazia(pilhadodisparador)) {
                pilhadodisparador = botao(listadisp[i], a);
                printf("Disparando um objeto: %d\n", tipoatualnodisparo(listadisp[i]));
                adicionar(&filasaida, disparar(listadisp[i], x1, y1), tipoatualnodisparo(listadisp[i]));
                x1 += x2;
                y1 += y2;
            }
        }
        else if (!strcmp(comando, "shft")) {
            fscanf(fileq, "%i %c %i", &i, &a, &n);
            printf("REALIZANDO SHIFT\n");
            for (j=0; j<n; j++) {
                botao(listadisp[i], a);
            }
            printf("SHIFT REALIZADO PARA %c\n", a);
        }
        else if (!strcmp(comando, "dsp")) {
            double nx, ny;
            fscanf(fileq, "%i %lf %lf", &i, &nx, &ny);
            printf("Disparando um objeto: %d\n", tipoatualnodisparo(listadisp[i]));
            adicionar(&filasaida, disparar(listadisp[i], nx, ny), tipoatualnodisparo(listadisp[i]));
        }
    } while (1);

    exibirfila(filasaida, filesaidaquery);
    fprintf(filesaidaquery, "</svg>\n");
}