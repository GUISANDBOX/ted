#include "comandosqry.h"
#include <string.h>
#include <stdio.h>
#include "retangulo.h"
#include "circulo.h"
#include "linha.h"
#include "texto.h"
#include "ponto.h"
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
        escreveLinhaTxt(l, arqtxt);
    } else if (tipo == 4) { // Texto
        Texto t = (Texto)item;
        escreveTextoTxt(t, arqtxt);
    }
}

Ponto getP1Item(Item item, int tipo) {
    if (tipo == 3) { // Linha
        Linha l = (Linha)item;
        return criaPonto(getX1Linha(l), getY1Linha(l));
    }
    else if (tipo == 4) {
        Texto t = (Texto)item;
        return getP1Texto(t);
    }
    return NULL; // Outros tipos não possuem ponto 1
}


Ponto getP2Item(Item item, int tipo) {
    if (tipo == 3) { // Linha
        Linha l = (Linha)item;
        return criaPonto(getX2Linha(l), getY2Linha(l));
    }
    else if (tipo == 4) {
        Texto t = (Texto)item;
        return getP2Texto(t);
    }
    return NULL; // Outros tipos não possuem ponto 1
}

double areaLinha(Item item, int tipo) {
    if (tipo == 3) { // Linha
        Linha l = (Linha)item;
        return getAreaLinha(l);
    }
    else if (tipo == 4) {
        Texto t = (Texto)item;
        return getAreaTexto(t);
    }
    return 0.0; // Outros tipos não possuem área de linha
}

char *getCorbLinha(Item item, int tipo) {
    if (tipo == 3) { // Linha
        Linha l = (Linha)item;
        return getCorLinha(l);
    }
    else if (tipo == 4) {
        Texto t = (Texto)item;
        return getCorbTexto(t);
    }
    return NULL; // Outros tipos não possuem cor de linha
}


char *getCorpLinha(Item item, int tipo) {
    if (tipo == 3) { // Linha
        Linha l = (Linha)item;
        return getCorLinha(l);
    }
    else if (tipo == 4) {
        Texto t = (Texto)item;
        return getCorpTexto(t);
    }
    return NULL; // Outros tipos não possuem cor de linha
}

int getIdLinhaOuTexto(Item li, int tipo_i) {
    if (tipo_i == 3) { // Linha
        Linha l = (Linha)li;
        return getIdLinha(l);
    }
    else if (tipo_i == 4) {
        Texto t = (Texto)li;
        return getIdTexto(t);
    }
    return -1; // Outros tipos não possuem id de linha ou texto
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
    char mododisp; 

    
    int totaldeinstrucoes = 0;
    int totaldedisparos = 0;
    int totaldeformasesmagadas = 0;
    int totaldeformasclonadas = 0;  
    double pontuacaofinal = 0.0;

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
            totaldeinstrucoes++;
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
            totaldeinstrucoes++;
        }
        else if (!strcmp(comando, "atch")) {
            fscanf(fileq, "%d %d %d", &i, &iesq, &idir);
            printf("Encaixando disparadores!\n");
            encaixar(listadisp[i], listacarr[iesq], listacarr[idir]);
            printf("Encaixe realizado!\n");
            totaldeinstrucoes++;
        }
        else if (!strcmp(comando, "rjd")) {
            fscanf(fileq, "%i %c %f %f %f %f", &i, &a, &x1, &y1, &x2, &y2);
            printf("REALIZANDO RAJADA\n");
            Pilha pilhadodisparador;
            
            pilhadodisparador = (a=='d') ? getPilhaEsq(listadisp[i]) : getPilhaDir(listadisp[i]);
            
            while(!pilhavazia(pilhadodisparador)) {
                pilhadodisparador = botao(listadisp[i], a);
                printf("Disparando um objeto: %d\n", tipoatualnodisparo(listadisp[i]));
                // TODO verificar se é para escrever o item antes de disparar ou depois do disparo na sua posição final
                escreveItemTxt(itemAtualNoDisparo(listadisp[i]), tipoatualnodisparo(listadisp[i]), arqtxt);
                adicionar(&filasaida, disparar(listadisp[i], x1, y1), tipoatualnodisparo(listadisp[i]));
                x1 += x2;
                y1 += y2;
                totaldedisparos++;
            }
            totaldeinstrucoes++;
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
            totaldeinstrucoes++;
        }
        else if (!strcmp(comando, "dsp")) {
            double nx, ny;
            fscanf(fileq, "%i %lf %lf %c", &i, &nx, &ny, &mododisp);
            printf("Disparando um objeto: %d\n", tipoatualnodisparo(listadisp[i]));
            fprintf(arqtxt, "[*] dsp %d %.2lf %.2lf %c\n", i, nx, ny, mododisp);
            escreveItemTxt(itemAtualNoDisparo(listadisp[i]), tipoatualnodisparo(listadisp[i]), arqtxt);
            Item itemdisparado = disparar(listadisp[i], nx, ny);
            int tipodisparado = tipoatualnodisparo(listadisp[i]);
            adicionar(&filasaida, itemdisparado, tipodisparado);
            fprintf(arqtxt,"Posicao apos disparo: (%.2lf, %.2lf)\n\n", getXDisparador(listadisp[i]) + nx, getYDisparador(listadisp[i]) + ny);
            totaldeinstrucoes++;
            totaldedisparos++;
        }
        else if (!strcmp(comando, "calc")) {
            printf("REALIZANDO CALC\n");
            filaOriginal = executaCalc(filasaida, filaOriginal, filesaidaquery, arqtxt, &totaldeformasesmagadas, &totaldeformasclonadas, &pontuacaofinal);
            totaldeinstrucoes++;
        }
    } while (1);

    //exibirfila(filasaida, filesaidaquery);
    exibirfila(filaOriginal, filesaidaquery);
    fprintf(filesaidaquery, "</svg>\n");
    fprintf(arqtxt, "\nPontuação final: %lf\nNúmero total de instruções executadas: %d\nNúmero total de disparos: %d\nNúmero total de formas esmagadas: %d\nNúmero total de formas clonadas: %d", pontuacaofinal, totaldeinstrucoes, totaldedisparos, totaldeformasesmagadas, totaldeformasclonadas);

    // Limpa os disparadores e pilhas
    for (j=0; j<100; j++) {
        limpaDisparador(&listadisp[j]);
        limpaPilha(&listacarr[j]);
    }
}

Fila executaCalc(Fila filasaida, Fila filaOriginal, FILE *filesaidaquery, FILE *arqtxt, int *totaldeformasesmagadas, int *totaldeformasclonadas, double *pontuacaofinal) {
    int tipo_i = 0, tipo_j = 0, tipo = 0;
    Texto asterisco;
    double pontosround = 0;
    int maior_id = getMaiorIdFIla(filasaida) + 1;
    while (!filavazia(filasaida)) {
        pontosround = 0; // Zera a pontuação a cada iteração
        Item item_i = remover(&filasaida, &tipo_i);
        Item item_j = remover(&filasaida, &tipo_j);
        if (tipo_i == 2 && tipo_j == 2) { // Ambos são retângulos
            Retangulo ri = (Retangulo)item_i;
            Retangulo rj = (Retangulo)item_j;
            if (retangulosSobrepoem(ri, rj)) {
                fprintf(arqtxt, "Retângulos se sobrepõem!\n");
                if (areaRetangulo(rj) >= areaRetangulo(ri)) {
                    fprintf(arqtxt, "Retângulo %d é maior ou igual. Esmagando o retangulo %d.\n", getIdRetangulo(rj), getIdRetangulo(ri));
                    //adicionar(&filasaida, r1, tipo_i);
                    asterisco = criaTexto(criaPonto(getXRetangulo(ri), getYRetangulo(ri)), "red", "red", "*", 'a', "Arial", "normal", "12", 0);
                    adicionar(&filaOriginal, asterisco, 4);
                    adicionar(&filaOriginal, rj, tipo_j);
                    (*totaldeformasesmagadas)++;
                    pontosround += areaRetangulo(ri); // Pontuação = area da figura esmagada
                } else {
                    fprintf(arqtxt, "Retângulo %d eh menor. Invertendo cores e clonando %d com novo ID %d.\n", getIdRetangulo(rj), getIdRetangulo(ri), maior_id);
                    //adicionar(&filasaida, r2, tipo_j);
                    setCorbRetangulo(rj, getCorpRetangulo(ri)); // Altera a cor de borda do rj para a cor de preenchimento do ri
                    Retangulo cloneret = cloneretangulo(ri, maior_id); // Clona o retângulo invertido
                    adicionar(&filaOriginal, ri, tipo_i);
                    adicionar(&filaOriginal, rj, tipo_j);
                    adicionar(&filaOriginal, cloneret, tipo_i);
                    (*totaldeformasclonadas)++;
                }

            } else {
                fprintf(arqtxt, "Retângulos não se sobrepõem.\n");
                adicionar(&filaOriginal, ri, tipo_i);
                adicionar(&filaOriginal, rj, tipo_j);
            }
        }
        else if (tipo_i == 1 && tipo_j == 1) { // Ambos são círculos
            Circulo ci = (Circulo)item_i;
            Circulo cj = (Circulo)item_j;
            if (circulosSobrepoem(ci, cj)) {
                fprintf(arqtxt, "Círculos se sobrepõem!\n");
                if (areaCirculo(cj) >= areaCirculo(ci)) {
                    fprintf(arqtxt, "Círculo %d é maior ou igual. Esmagando o círculo %d.\n", getIdCirculo(cj), getIdCirculo(ci));
                    //adicionar(&filasaida, c1, tipo_i);
                    adicionar(&filaOriginal, cj, tipo_j);
                    (*totaldeformasesmagadas)++;
                    pontosround += areaCirculo(ci); // Pontuação = area da figura esmagada
                } else {
                    fprintf(arqtxt, "Círculo %d eh menor. Invertendo cores e clonando %d com novo ID %d.\n", getIdCirculo(cj), getIdCirculo(ci), maior_id);
                    //adicionar(&filasaida, c2, tipo_j);
                    setCorbCirculo(cj, getCorpCirculo(ci)); // Altera a cor de borda do cj para a cor de preenchimento do ci
                    Circulo clonecirc = clonecirculo(ci, maior_id); // Clona o círculo invertido
                    adicionar(&filaOriginal, ci, tipo_i);
                    adicionar(&filaOriginal, cj, tipo_j);
                    adicionar(&filaOriginal, clonecirc, tipo_i);
                    (*totaldeformasclonadas)++;
                }
            } else {
                fprintf(arqtxt, "Círculos não se sobrepõem.\n");
                adicionar(&filaOriginal, ci, tipo_i);
                adicionar(&filaOriginal, cj, tipo_j);
            }
        } 
        else if ((tipo_i == 1 && tipo_j == 2)) { // O primeiro é circulo e o segundo é retângulo (retangulo sobre o circulo)
            Circulo ci = (Circulo)item_i;
            Retangulo rj = (Retangulo)item_j;
            if (circuloRetanguloSobrepoem(ci, rj)) {
                fprintf(arqtxt, "Círculo e Retângulo se sobrepõem!\n");
                // Lógica de sobreposição pode ser adicionada aqui
                if (areaRetangulo(rj) >= areaCirculo(ci)) {
                    fprintf(arqtxt, "Retângulo %d é maior ou igual. Esmagando o círculo %d.\n", getIdRetangulo(rj), getIdCirculo(ci));
                    adicionar(&filaOriginal, rj, tipo_j); // Adiciona retangulo na fila original, pois ela esmagou o circulo
                    (*totaldeformasesmagadas)++;
                    pontosround += areaCirculo(ci); // Pontuação = area da figura esmagada
                } else {
                    fprintf(arqtxt, "Círculo %d é maior. Invertendo cores e clonando %d com novo ID %d.\n", getIdCirculo(ci), getIdCirculo(ci), maior_id);
                    setCorbRetangulo(rj, getCorpCirculo(ci)); // Altera a cor de borda do rj para a cor de preenchimento do ci (circulo)
                    Circulo clonecirc = clonecirculo(ci, maior_id); // Clona o círculo invertido
                    adicionar(&filaOriginal, ci, tipo_i);
                    adicionar(&filaOriginal, rj, tipo_j);
                    adicionar(&filaOriginal, clonecirc, tipo_i);
                    (*totaldeformasclonadas)++;
                }
            } else {
                fprintf(arqtxt, "Círculo e Retângulo não se sobrepõem.\n");
                adicionar(&filaOriginal, ci, tipo_i);
                adicionar(&filaOriginal, rj, tipo_j);
            }
           
        } 
        else if ((tipo_i == 2 && tipo_j == 1)) { // O primeiro é retângulo e o segundo é círculo (circulo sobre o retangulo)
            Retangulo ri = (Retangulo)item_i;
            Circulo cj = (Circulo)item_j;
            if (circuloRetanguloSobrepoem(cj, ri)) {
                fprintf(arqtxt, "Retângulo e Círculo se sobrepõem!\n");
                // Lógica de sobreposição pode ser adicionada aqui
                if (areaCirculo(cj) >= areaRetangulo(ri)) {
                    fprintf(arqtxt, "Círculo %d é maior ou igual. Esmagando o retângulo %d.\n", getIdCirculo(cj), getIdRetangulo(ri));
                    adicionar(&filaOriginal, cj, tipo_j); // Adiciona circulo na fila original, pois ela esmagou o retangulo
                    (*totaldeformasesmagadas)++;
                    pontosround += areaRetangulo(ri); // Pontuação = area da figura esmagada
                } else {
                    fprintf(arqtxt, "Retângulo %d eh menor. Invertendo cores e clonando %d com novo ID %d.\n", getIdRetangulo(ri), getIdRetangulo(ri), maior_id);
                    setCorbCirculo(cj, getCorpRetangulo(ri)); // Altera a cor de borda do cj para a cor de preenchimento do ri
                    Retangulo cloneret = cloneretangulo(ri, maior_id); // Clona o retângulo invertido
                    adicionar(&filaOriginal, ri, tipo_i);
                    adicionar(&filaOriginal, cj, tipo_j);
                    adicionar(&filaOriginal, cloneret, tipo_i);
                    (*totaldeformasclonadas)++;
                }
            } else {
                printf("Retângulo e Círculo não se sobrepõem.\n");
                 adicionar(&filaOriginal, ri, tipo_i);
                adicionar(&filaOriginal, cj, tipo_j);
            }
        }
        else if (linhaOuTexto(tipo_i) && linhaOuTexto(tipo_j)) { // Linha e linha (que podem ser tanto textos como linhas, mas aqui são tratados como linhas)
            Item li = item_i;
            Item lj = item_j;
            if (linhasSobrepoem(li, lj, tipo_i, tipo_j)) {
                fprintf(arqtxt, "Linhas/Textos se sobrepõem!\n");
                if (areaLinha(lj, tipo_j) >= areaLinha(li, tipo_i)) {
                    fprintf(arqtxt, "Linha/Texto %d é maior ou igual. Esmagando o Linha/Texto %d.\n", getIdLinhaOuTexto(lj, tipo_j), getIdLinhaOuTexto(li, tipo_i));
                    adicionar(&filaOriginal, lj, tipo_j);
                    (*totaldeformasesmagadas)++;
                    pontosround += areaLinha(li, tipo_i); // Pontuação = area da figura esmagada
                } else {
                    fprintf(arqtxt, "Linha/Texto %d é menor. Invertendo cores e clonando %d com novo ID %d.\n", getIdLinhaOuTexto(li, tipo_i), getIdLinhaOuTexto(li, tipo_i), maior_id);
                    // Invertendo cores
                    char *corb_li = getCorbLinha(li, tipo_i);
                    char *corp_li = getCorpLinha(li, tipo_i);
                    if (tipo_j == 3) { // Linha
                        Linha lj_linha = (Linha)lj;
                        setCorLinha(lj_linha, corp_li); // Altera a cor da linha para a cor de preenchimento do li
                    } else if (tipo_j == 4) { // Texto
                        Texto lj_texto = (Texto)lj;
                        setCorbTexto(lj_texto, corp_li); // Altera a cor de borda do texto para a cor de preenchimento do li
                    }
                    // Clonando
                    Item clone_li;
                    if (tipo_i == 3) { // Linha
                        Linha li_linha = (Linha)li;
                        clone_li = cloneLinha(li_linha, maior_id);
                    } else if (tipo_i == 4) { // Texto
                        Texto li_texto = (Texto)li;
                        clone_li = cloneTexto(li_texto, maior_id);
                    }
                    adicionar(&filaOriginal, li, tipo_i);
                    adicionar(&filaOriginal, lj, tipo_j);
                    adicionar(&filaOriginal, clone_li, tipo_i);
                    (*totaldeformasclonadas)++;
                }
            } else {
                fprintf(arqtxt, "Linhas/Textos não se sobrepõem.\n");
                adicionar(&filaOriginal, li, tipo_i);
                adicionar(&filaOriginal, lj, tipo_j);
            }
        }
        else if (tipo_i == 1 && linhaOuTexto(tipo_j)) { // Circulo e linha/texto
            Circulo ci = (Circulo)item_i;
            Item lj = item_j;
            // Implementar lógica de sobreposição círculo-linha/texto se necessário
            if (circuloLinhaSobrepoem(ci, lj, tipo_j)) {
                fprintf(arqtxt, "Linha/Texto e Círculo se sobrepõem!\n");
                if (areaLinha(lj, tipo_j) >= areaCirculo(ci)) {
                    fprintf(arqtxt, "Linha/Texto %d é maior ou igual. Esmagando o Círculo %d.\n", getIdLinhaOuTexto(lj, tipo_j), getIdCirculo(ci));
                    adicionar(&filaOriginal, lj, tipo_j);
                    (*totaldeformasesmagadas)++;
                    pontosround += areaCirculo(ci); // Pontuação = area da figura esmagada
                } else {
                    fprintf(arqtxt, "Círculo %d é maior. Invertendo cores e clonando %d com novo ID %d.\n", getIdCirculo(ci), getIdCirculo(ci), maior_id);
                    setCorbCirculo(ci, getCorpLinha(lj, tipo_j)); // Altera a cor de borda do círculo para a cor de preenchimento da linha/texto
                    Item clonecirc = clonecirculo(ci, maior_id); // Clona o círculo invertido
                    adicionar(&filaOriginal, ci, tipo_i);
                    adicionar(&filaOriginal, lj, tipo_j);
                    adicionar(&filaOriginal, clonecirc, tipo_i);
                    (*totaldeformasclonadas)++;
                }
            } else {
                fprintf(arqtxt, "Linha/Texto e Círculo não se sobrepõem.\n");
                adicionar(&filaOriginal, ci, tipo_i);
                adicionar(&filaOriginal, lj, tipo_j);
            }
            
        }
        else if (linhaOuTexto(tipo_i) && tipo_j == 1) { // Linha/texto e círculo
            Item li = item_i;
            Circulo cj = (Circulo)item_j;
            // Implementar lógica de sobreposição linha/texto-círculo se necessário
            if (circuloLinhaSobrepoem(cj, li, tipo_i)) {
                fprintf(arqtxt, "Linha/Texto e Círculo se sobrepõem!\n");
                if (areaCirculo(cj) >= areaLinha(li, tipo_i)) {
                    fprintf(arqtxt, "Círculo %d é maior ou igual. Esmagando o Linha/Texto %d.\n", getIdCirculo(cj), getIdLinhaOuTexto(li, tipo_i));
                    adicionar(&filaOriginal, cj, tipo_j);
                    (*totaldeformasesmagadas)++;
                    pontosround += areaLinha(li, tipo_i); // Pontuação = area da figura esmagada
                } else {
                    fprintf(arqtxt, "Linha/Texto %d é maior. Invertendo cores e clonando %d com novo ID %d.\n", getIdLinhaOuTexto(li, tipo_i), getIdCirculo(cj), maior_id);
                    // Invertendo cores
                    char *corb_li = getCorbLinha(li, tipo_i);
                    char *corp_li = getCorpLinha(li, tipo_i);
                    setCorbCirculo(cj, corp_li); // Altera a cor de borda do círculo para a cor de preenchimento da linha/texto
                    // Clonando
                    Item clone_li;
                    if (tipo_i == 3) { // Linha
                        Linha li_linha = (Linha)li;
                        clone_li = cloneLinha(li_linha, maior_id);
                    } else if (tipo_i == 4) { // Texto
                        Texto li_texto = (Texto)li;
                        clone_li = cloneTexto(li_texto, maior_id);
                    }
                    adicionar(&filaOriginal, li, tipo_i);
                    adicionar(&filaOriginal, cj, tipo_j);
                    adicionar(&filaOriginal, clone_li, tipo_i);
                    (*totaldeformasclonadas)++;
                }
            } else {
                fprintf(arqtxt, "Linha/Texto e Círculo não se sobrepõem.\n");
                adicionar(&filaOriginal, li, tipo_i);
                adicionar(&filaOriginal, cj, tipo_j);
            }
            
        }
        else if (tipo_i == 2 && linhaOuTexto(tipo_j)) { // Retângulo e linha/texto
            Retangulo ri = (Retangulo)item_i;
            Item lj = item_j;
            // Implementar lógica de sobreposição retângulo-linha/texto se necessário
            if (retanguloLinhaSobrepoem(ri, lj, tipo_j)) {
                fprintf(arqtxt, "Linha/Texto e Retângulo se sobrepõem!\n");
                if (areaLinha(lj, tipo_j) >= areaRetangulo(ri)) {
                    fprintf(arqtxt, "Linha/Texto %d é maior ou igual. Esmagando o Retângulo %d.\n", getIdLinhaOuTexto(lj, tipo_j), getIdRetangulo(ri));
                    adicionar(&filaOriginal, lj, tipo_j);
                    (*totaldeformasesmagadas)++;
                    pontosround += areaRetangulo(ri); // Pontuação = area da figura esmagada
                } else {
                    fprintf(arqtxt, "Retângulo %d é maior. Invertendo cores e clonando %d com novo ID %d.\n", getIdRetangulo(ri), getIdLinhaOuTexto(lj, tipo_j), maior_id);
                    setCorbRetangulo(ri, getCorpLinha(lj, tipo_j)); // Altera a cor de borda do retângulo para a cor de preenchimento da linha/texto
                    Retangulo cloneret = cloneretangulo(ri, maior_id); // Clona o retângulo invertido
                    adicionar(&filaOriginal, ri, tipo_i);
                    adicionar(&filaOriginal, lj, tipo_j);
                    adicionar(&filaOriginal, cloneret, tipo_i);
                    (*totaldeformasclonadas)++;
                }
            } else {
                fprintf(arqtxt, "Linha/Texto e Retângulo não se sobrepõem.\n");
                adicionar(&filaOriginal, ri, tipo_i);
                adicionar(&filaOriginal, lj, tipo_j);
            }
        }
        else if (linhaOuTexto(tipo_i) && tipo_j == 2) { // Linha/texto e retângulo
            Item li = item_i;
            Retangulo rj = (Retangulo)item_j;
            // Implementar lógica de sobreposição linha/texto-retângulo se necessário
            if (retanguloLinhaSobrepoem(rj, li, tipo_i)) {
                fprintf(arqtxt, "Linha/Texto e Retângulo se sobrepõem!\n");
                if (areaRetangulo(rj) >= areaLinha(li, tipo_i)) {
                    fprintf(arqtxt, "Retângulo %d é maior ou igual. Esmagando o Linha/Texto %d\n", getIdRetangulo(rj), getIdLinhaOuTexto(li, tipo_i));
                    adicionar(&filaOriginal, rj, tipo_j);
                    (*totaldeformasesmagadas)++;
                    pontosround += areaLinha(li, tipo_i); // Pontuação = area da figura esmagada
                } else {
                    fprintf(arqtxt, "Linha/Texto %d e maior. Invertendo cores e clonando %d com novo ID %d.\n", getIdLinhaOuTexto(li, tipo_i), getIdRetangulo(rj), maior_id);
                    // Invertendo cores
                    char *corb_li = getCorbLinha(li, tipo_i);
                    char *corp_li = getCorpLinha(li, tipo_i);
                    setCorbRetangulo(rj, corp_li); // Altera a cor de borda do retângulo para a cor de preenchimento da linha/texto
                    // Clonando
                    Item clone_li;
                    if (tipo_i == 3) { // Linha
                        Linha li_linha = (Linha)li;
                        clone_li = cloneLinha(li_linha, maior_id);
                    } else if (tipo_i == 4) { // Texto
                        Texto li_texto = (Texto)li;
                        clone_li = cloneTexto(li_texto, maior_id);
                    }
                    adicionar(&filaOriginal, li, tipo_i);
                    adicionar(&filaOriginal, rj, tipo_j);
                    adicionar(&filaOriginal, clone_li, tipo_i);
                    (*totaldeformasclonadas)++;
                }
            } else {
                fprintf(arqtxt, "Linha/Texto e Retângulo não se sobrepõem.\n");
                adicionar(&filaOriginal, li, tipo_i);
                adicionar(&filaOriginal, rj, tipo_j);
            }
            
        }
        //adicionar(&filaOriginal, item, tipo);
        (*pontuacaofinal) = (*pontuacaofinal) + pontosround;
        maior_id++;
        fprintf(arqtxt, "Area esmagada no round: %lf\n", pontosround);
    }
    return filaOriginal;
}

int linhaOuTexto(int tipo) {
    return (tipo == 3 || tipo == 4);
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

int linhasSobrepoem(Item l1, Item l2, int tipo1, int tipo2) {
    printf("A PONTOS OBTIDOS\n");
    Ponto p1 = getP1Item(l1, tipo1);
    Ponto p2 = getP2Item(l2, tipo2);
    printf("PONTOS OBTIDOS\n");
    double p1x1 = getX(p1);
    double p1y1 = getY(p1);
    double p1x2 = getX(p1);
    double p1y2 = getY(p1);

    double p2x1 = getX(p2);
    double p2y1 = getY(p2);
    double p2x2 = getX(p2);
    double p2y2 = getY(p2);

    const double EPS = 1e-9;

    // Orientações (área com sinal dos triângulos)
    double o1 = (p1x2 - p1x1)*(p2y1 - p1y1) - (p1y2 - p1y1)*(p2x1 - p1x1);
    double o2 = (p1x2 - p1x1)*(p2y2 - p1y1) - (p1y2 - p1y1)*(p2x2 - p1x1);
    double o3 = (p2x2 - p2x1)*(p1y1 - p2y1) - (p2y2 - p2y1)*(p1x1 - p2x1);
    double o4 = (p2x2 - p2x1)*(p1y2 - p2y1) - (p2y2 - p2y1)*(p1x2 - p2x1);

    // Sinais com tolerância
    int s1 = (o1 >  EPS) - (o1 < -EPS);
    int s2 = (o2 >  EPS) - (o2 < -EPS);
    int s3 = (o3 >  EPS) - (o3 < -EPS);
    int s4 = (o4 >  EPS) - (o4 < -EPS);

    // Caso geral: cruzam estritamente
    if (s1*s2 < 0 && s3*s4 < 0) return 1;

    // Casos de toque/sobreposição colinear:
    // C em AB
    if (s1 == 0 &&
        p2x1 >= fmin(p1x1, p1x2) - EPS && p2x1 <= fmax(p1x1, p1x2) + EPS &&
        p2y1 >= fmin(p1y1, p1y2) - EPS && p2y1 <= fmax(p1y1, p1y2) + EPS)
        return 1;

    // D em AB
    if (s2 == 0 &&
        p2x2 >= fmin(p1x1, p1x2) - EPS && p2x2 <= fmax(p1x1, p1x2) + EPS &&
        p2y2 >= fmin(p1y1, p1y2) - EPS && p2y2 <= fmax(p1y1, p1y2) + EPS)
        return 1;

    // A em CD
    if (s3 == 0 &&
        p1x1 >= fmin(p2x1, p2x2) - EPS && p1x1 <= fmax(p2x1, p2x2) + EPS &&
        p1y1 >= fmin(p2y1, p2y2) - EPS && p1y1 <= fmax(p2y1, p2y2) + EPS)
        return 1;

    // B em CD
    if (s4 == 0 &&
        p1x2 >= fmin(p2x1, p2x2) - EPS && p1x2 <= fmax(p2x1, p2x2) + EPS &&
        p1y2 >= fmin(p2y1, p2y2) - EPS && p1y2 <= fmax(p2y1, p2y2) + EPS)
        return 1;
        
    return 0; // Placeholder: implementar lógica real se necessário
}

int circuloLinhaSobrepoem(Circulo c, Item l, int tipo_l) {
    // Pega centro e raio do círculo
    double cx = getXCirculo(c);
    double cy = getYCirculo(c);
    double r = getRCirculo(c);

    // Obtém os pontos extremos do item de linha/texto
    Ponto p1 = getP1Item(l, tipo_l);
    Ponto p2 = getP2Item(l, tipo_l);
    if (!p1 || !p2) return 0;

    double x1 = getX(p1);
    double y1 = getY(p1);
    double x2 = getX(p2);
    double y2 = getY(p2);

    // Vetor do segmento AB
    double abx = x2 - x1;
    double aby = y2 - y1;
    double ab2 = abx*abx + aby*aby;

    // Caso degenerado: segmento de comprimento zero
    if (ab2 == 0.0) {
        double dx = cx - x1;
        double dy = cy - y1;
        return (dx*dx + dy*dy) <= r*r;
    }

    // Projeção do centro C no segmento AB (parâmetro t clamped em [0,1])
    double acx = cx - x1;
    double acy = cy - y1;
    double t = (acx*abx + acy*aby) / ab2;
    if (t < 0.0) t = 0.0; else if (t > 1.0) t = 1.0;

    // Ponto mais próximo P = A + t*(B-A)
    double px = x1 + t*abx;
    double py = y1 + t*aby;

    // Distância de P ao centro do círculo
    double dx = px - cx;
    double dy = py - cy;
    return (dx*dx + dy*dy) <= r*r;
}

// Helper interno: orientação
static int orient(double ax, double ay, double bx, double by, double cx, double cy) {
    double val = (bx - ax)*(cy - ay) - (by - ay)*(cx - ax);
    const double EPS = 1e-9;
    if (val > EPS) return 1;     // anti-horário
    if (val < -EPS) return -1;   // horário
    return 0;                    // colinear
}

// Helper interno: checa se ponto C está no segmento AB (assumindo colinearidade)
static int on_segment(double ax, double ay, double bx, double by, double cx, double cy) {
    return (cx >= fmin(ax, bx) - 1e-9 && cx <= fmax(ax, bx) + 1e-9 &&
            cy >= fmin(ay, by) - 1e-9 && cy <= fmax(ay, by) + 1e-9);
}

// Helper interno: interseção entre segmentos AB e CD
static int intersecta_segmentos(double ax, double ay, double bx, double by,
                                double cx, double cy, double dx, double dy) {
    int o1 = orient(ax, ay, bx, by, cx, cy);
    int o2 = orient(ax, ay, bx, by, dx, dy);
    int o3 = orient(cx, cy, dx, dy, ax, ay);
    int o4 = orient(cx, cy, dx, dy, bx, by);

    if (o1*o2 < 0 && o3*o4 < 0) return 1; // interseção própria

    // Casos colineares/tangência
    if (o1 == 0 && on_segment(ax, ay, bx, by, cx, cy)) return 1;
    if (o2 == 0 && on_segment(ax, ay, bx, by, dx, dy)) return 1;
    if (o3 == 0 && on_segment(cx, cy, dx, dy, ax, ay)) return 1;
    if (o4 == 0 && on_segment(cx, cy, dx, dy, bx, by)) return 1;
    return 0;
}

int retanguloLinhaSobrepoem(Retangulo r, Item l, int tipo_l) {
    // Limites do retângulo alinhado aos eixos
    double rx = getXRetangulo(r);
    double ry = getYRetangulo(r);
    double rw = getWRetangulo(r);
    double rh = getHRetangulo(r);
    double xmin = rx;
    double xmax = rx + rw;
    double ymin = ry;
    double ymax = ry + rh;

    // Segmento (linha/texto)
    Ponto p1 = getP1Item(l, tipo_l);
    Ponto p2 = getP2Item(l, tipo_l);
    if (!p1 || !p2) return 0;
    double x1 = getX(p1);
    double y1 = getY(p1);
    double x2 = getX(p2);
    double y2 = getY(p2);

    // 1) Algum extremo dentro do retângulo
    int p1_dentro = (x1 >= xmin && x1 <= xmax && y1 >= ymin && y1 <= ymax);
    int p2_dentro = (x2 >= xmin && x2 <= xmax && y2 >= ymin && y2 <= ymax);
    if (p1_dentro || p2_dentro) return 1;

    // 2) Interseção com as 4 arestas do retângulo
    // Arestas: (xmin,ymin)-(xmax,ymin), (xmax,ymin)-(xmax,ymax),
    //          (xmax,ymax)-(xmin,ymax), (xmin,ymax)-(xmin,ymin)
    if (intersecta_segmentos(x1, y1, x2, y2, xmin, ymin, xmax, ymin)) return 1; // base inferior
    if (intersecta_segmentos(x1, y1, x2, y2, xmax, ymin, xmax, ymax)) return 1; // lateral direita
    if (intersecta_segmentos(x1, y1, x2, y2, xmax, ymax, xmin, ymax)) return 1; // topo
    if (intersecta_segmentos(x1, y1, x2, y2, xmin, ymax, xmin, ymin)) return 1; // lateral esquerda

    return 0;
}
