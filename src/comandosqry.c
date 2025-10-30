#include "comandosqry.h"
#include <string.h>
#include <stdio.h>
#include "retangulo.h"
#include "circulo.h"
#include "linha.h"
#include "texto.h"
#include <math.h>
#include "disparador.h"

void escreveItemTxt(Item item, int tipo, FILE *arqtxt) {
    if (tipo == 1) { // Circulo
        Circulo c = (Circulo)item;
        escreveCirculoTxt(c, arqtxt);
    } else if (tipo == 2) { // Retangulo
        Retangulo r = (Retangulo)item;
        escreveRetanguloTxt(r, arqtxt);
    } else if (tipo == 3) { // Linha
        Linha l = (Linha)item;
        
    } else if (tipo == 4) { // Texto
        Texto t = (Texto)item;
        
    }
}

/**
 * O arqtxt é o arquivo txt de saída para comandos qry que precisem escrever nele.
 */
void processaQry(FILE *fileq, Fila filasaida, FILE *filesaidaquery, Fila filaOriginal, FILE *arqtxt) {
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
            fprintf(arqtxt, "[*] lc %d %d\n", i, n);
            Pilha pilha = criapilha(0);
            Item item;
            for (j=0; j<n; j++) {
                item = remover(&filaOriginal, &tipo);
                empilha(&pilha, item, tipo);
                escreveItemTxt(item, tipo, arqtxt);
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
            fprintf(arqtxt, "[*] shft %d %c %d\n", i, a, n);
            for (j=0; j<n; j++) {
                botao(listadisp[i], a);
            }
            escreveItemTxt(itemAtualNoDisparo(listadisp[i]), tipoatualnodisparo(listadisp[i]), arqtxt);
            printf("SHIFT REALIZADO PARA %c\n", a);
        }
        else if (!strcmp(comando, "dsp")) {
            double nx, ny;
            fscanf(fileq, "%i %lf %lf", &i, &nx, &ny);
            printf("Disparando um objeto: %d\n", tipoatualnodisparo(listadisp[i]));
            adicionar(&filasaida, disparar(listadisp[i], nx, ny), tipoatualnodisparo(listadisp[i]));
        }
        else if (!strcmp(comando, "calc")) {
            printf("REALIZANDO CALC\n");
            filaOriginal = executaCalc(filasaida, filaOriginal, filesaidaquery);
        }
    } while (1);

    //exibirfila(filasaida, filesaidaquery);
    exibirfila(filaOriginal, filesaidaquery);
    fprintf(filesaidaquery, "</svg>\n");
}

Fila executaCalc(Fila filasaida, Fila filaOriginal, FILE *filesaidaquery) {
    int tipo_i = 0, tipo_j = 0, tipo = 0;
    Texto asterisco;
    while (!filavazia(filasaida)) {
        Item item_i = remover(&filasaida, &tipo_i);
        Item item_j = remover(&filasaida, &tipo_j);
        if (tipo_i == 2 && tipo_j == 2) { // Ambos são retângulos
            Retangulo ri = (Retangulo)item_i;
            Retangulo rj = (Retangulo)item_j;
            if (retangulosSobrepoem(ri, rj)) {
                printf("Retângulos se sobrepõem!\n");
                if (areaRetangulo(rj) >= areaRetangulo(ri)) {
                    printf("Retângulo J é maior ou igual. Esmagando o retangulo I.\n");
                    //adicionar(&filasaida, r1, tipo_i);
                    asterisco = criaTexto(criaPonto(getXRetangulo(ri), getYRetangulo(ri)), "red", "red", "*", 'a', "Arial", "normal", "12", 0);
                    adicionar(&filaOriginal, asterisco, 4);
                    adicionar(&filaOriginal, rj, tipo_j);
                } else {
                    printf("Retângulo J eh menor. Invertendo cores e clonando.\n");
                    //adicionar(&filasaida, r2, tipo_j);
                    setCorbRetangulo(rj, getCorpRetangulo(ri)); // Altera a cor de borda do rj para a cor de preenchimento do ri
                    Retangulo cloneret = cloneretangulo(ri, 1); // Clona o retângulo invertido
                    adicionar(&filaOriginal, ri, tipo_i);
                    adicionar(&filaOriginal, rj, tipo_j);
                    adicionar(&filaOriginal, cloneret, tipo_i);
                }

            } else {
                printf("Retângulos não se sobrepõem.\n");
                adicionar(&filaOriginal, ri, tipo_i);
                adicionar(&filaOriginal, rj, tipo_j);
            }
        }
        else if (tipo_i == 1 && tipo_j == 1) { // Ambos são círculos
            Circulo ci = (Circulo)item_i;
            Circulo cj = (Circulo)item_j;
            if (circulosSobrepoem(ci, cj)) {
                printf("Círculos se sobrepõem!\n");
                if (areaCirculo(cj) >= areaCirculo(ci)) {
                    printf("Círculo J é maior ou igual. Esmagando o retangulo I.\n");
                    //adicionar(&filasaida, c1, tipo_i);
                    adicionar(&filaOriginal, cj, tipo_j);
                } else {
                    printf("Círculo J é menor. Invertendo cores e clonando.\n");
                    //adicionar(&filasaida, c2, tipo_j);
                    setCorbCirculo(cj, getCorpCirculo(ci)); // Altera a cor de borda do cj para a cor de preenchimento do ci
                    Circulo clonecirc = clonecirculo(ci, 1); // Clona o círculo invertido
                    adicionar(&filaOriginal, ci, tipo_i);
                    adicionar(&filaOriginal, cj, tipo_j);
                    adicionar(&filaOriginal, clonecirc, tipo_i);
                }
            } else {
                printf("Círculos não se sobrepõem.\n");
                adicionar(&filaOriginal, ci, tipo_i);
                adicionar(&filaOriginal, cj, tipo_j);
            }
        } 
        else if ((tipo_i == 1 && tipo_j == 2)) { // O primeiro é circulo e o segundo é retângulo (retangulo sobre o circulo)
            Circulo ci = (Circulo)item_i;
            Retangulo rj = (Retangulo)item_j;
            if (circuloRetanguloSobrepoem(ci, rj)) {
                printf("Círculo e Retângulo se sobrepõem!\n");
                // Lógica de sobreposição pode ser adicionada aqui
                if (areaRetangulo(rj) >= areaCirculo(ci)) {
                    printf("Retângulo é maior ou igual. Esmagando o círculo.\n");
                    adicionar(&filaOriginal, rj, tipo_j); // Adiciona retangulo na fila original, pois ela esmagou o circulo
                } else {
                    printf("Círculo é maior. Invertendo cores e clonando.\n");
                    setCorbRetangulo(rj, getCorpCirculo(ci)); // Altera a cor de borda do rj para a cor de preenchimento do ci (circulo)
                    Circulo clonecirc = clonecirculo(ci, 1); // Clona o círculo invertido
                    adicionar(&filaOriginal, ci, tipo_i);
                    adicionar(&filaOriginal, rj, tipo_j);
                    adicionar(&filaOriginal, clonecirc, tipo_i);
                }
            } else {
                printf("Círculo e Retângulo não se sobrepõem.\n");
                adicionar(&filaOriginal, ci, tipo_i);
                adicionar(&filaOriginal, rj, tipo_j);
            }
           
        } 
        else if ((tipo_i == 2 && tipo_j == 1)) { // O primeiro é retângulo e o segundo é círculo (circulo sobre o retangulo)
            Retangulo ri = (Retangulo)item_i;
            Circulo cj = (Circulo)item_j;
            if (circuloRetanguloSobrepoem(cj, ri)) {
                printf("Retângulo e Círculo se sobrepõem!\n");
                // Lógica de sobreposição pode ser adicionada aqui
                if (areaCirculo(cj) >= areaRetangulo(ri)) {
                    printf("Circulo é maior ou igual. Esmagando o retangulo.\n");
                    adicionar(&filaOriginal, cj, tipo_j); // Adiciona circulo na fila original, pois ela esmagou o retangulo
                } else {
                    printf("Círculo é menor. Invertendo cores e clonando.\n");
                    setCorbCirculo(cj, getCorpRetangulo(ri)); // Altera a cor de borda do cj para a cor de preenchimento do ri
                    Retangulo cloneret = cloneretangulo(ri, 1); // Clona o retângulo invertido
                    adicionar(&filaOriginal, ri, tipo_i);
                    adicionar(&filaOriginal, cj, tipo_j);
                    adicionar(&filaOriginal, cloneret, tipo_i);
                }
            } else {
                printf("Retângulo e Círculo não se sobrepõem.\n");
                 adicionar(&filaOriginal, ri, tipo_i);
                adicionar(&filaOriginal, cj, tipo_j);
            }
           

        }
        
        printf("Adicionando item do tipo %d de volta à fila original.\n", tipo);
        //adicionar(&filaOriginal, item, tipo);
    }
    return filaOriginal;
}

int retangulosSobrepoem(Retangulo r1, Retangulo r2) {
    double x1_min = getXRetangulo(r1);
    double y1_min = getYRetangulo(r1);
    double x1_max = x1_min + getWRetangulo(r1);
    double y1_max = y1_min + getHRetangulo(r1);

    double x2_min = getXRetangulo(r2);
    double y2_min = getYRetangulo(r2);
    double x2_max = x2_min + getWRetangulo(r2);
    double y2_max = y2_min + getHRetangulo(r2);

    // Verifica se os retângulos não se sobrepõem
    if (x1_min >= x2_max || x2_min >= x1_max) return 0; // Não se sobrepõem horizontalmente
    if (y1_min >= y2_max || y2_min >= y1_max) return 0; // Não se sobrepõem verticalmente

    return 1; // Há sobreposição
}

int circulosSobrepoem(Circulo c1, Circulo c2) {
    double x1 = getXCirculo(c1);
    double y1 = getYCirculo(c1);
    double r1 = getRCirculo(c1);

    double x2 = getXCirculo(c2);
    double y2 = getYCirculo(c2);
    double r2 = getRCirculo(c2);

    double distancia_centros = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    double soma_raios = r1 + r2;

    if (distancia_centros < soma_raios) {
        return 1; // Há sobreposição
    } else {
        return 0; // Não há sobreposição
    }
}

int circuloRetanguloSobrepoem(Circulo c, Retangulo r) {
    double cx = getXCirculo(c);
    double cy = getYCirculo(c);
    double radius = getRCirculo(c);

    double rx = getXRetangulo(r);
    double ry = getYRetangulo(r);
    double rw = getWRetangulo(r);
    double rh = getHRetangulo(r);

    // Encontrar o ponto mais próximo do círculo dentro do retângulo
    double closestX = (cx < rx) ? rx : (cx > rx + rw) ? rx + rw : cx;
    double closestY = (cy < ry) ? ry : (cy > ry + rh) ? ry + rh : cy;

    // Calcular a distância entre o centro do círculo e esse ponto
    double distanceX = cx - closestX;
    double distanceY = cy - closestY;

    // Se a distância for menor que o raio, há sobreposição
    double distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
    return distanceSquared < (radius * radius);
}