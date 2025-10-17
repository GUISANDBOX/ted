#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "ponto.h"
#include "circulo.h"
#include "retangulo.h"
#include "Pilha.h"
#include "Fila.h"
#include "Lista.h"
#include "linha.h"
#include "texto.h"
#include "disparador.h"

#define PATH_LEN 250
#define FILE_NAME_LEN 100
#define MSG_LEN 1000

void trataPath(char *path, int tamMax, char* arg){
 int argLen = strlen(arg);
 assert(argLen<tamMax);
 if(arg[argLen-1]=='/'){
 arg[argLen-1]='\0';
 }
 strcpy(path,arg);
}

void trataNomeArquivo(char *path, int tamMax, char* arg){
 sprintf(path,"%s",arg);
}


int main(int argc, char *argv[]) {
    char dir[PATH_LEN], bed[PATH_LEN], arq[FILE_NAME_LEN], arqquery[FILE_NAME_LEN], dirsaidaqry[PATH_LEN], dirsaida[PATH_LEN], dirsaidabase[PATH_LEN];
    char *fullNameArq;

    int z;
    char comando[3];
    char a;
    int i=1;
    float x, y, x1, x2, y1, y2, r, w, h;
    char corb[100], corp[100], cor[100], txto[100], fFamily[100], fWeight[100], fSize[100];
    printf("Argumentos: %d\n", argc);
    while (i < argc){
         if (strcmp(argv[i],"-e")==0){
             i++;
             /* se i >= argc: ERRO-falta parametro */
             trataPath(dir,PATH_LEN, argv[i]);
             printf("LIDO DIRETORIO E: %s\n", dir);
             strcpy(bed, dir);
         }
         else if (strcmp(argv[i],"-f") == 0){
             i++;
             /* se i >= argc: ERRO-falta parametro */
             trataNomeArquivo(arq,FILE_NAME_LEN,argv[i]);
             printf("LIDO ARQ F: %s\n", arq);
         }
         else if (strcmp(argv[i],"-o") == 0){
             i++;
             /* se i >= argc: ERRO-falta parametro */
             trataNomeArquivo(dirsaida,PATH_LEN,argv[i]);
             strcpy(dirsaidabase, dirsaida);
         }
         else if (strcmp(argv[i],"-q") == 0){
             i++;
             /* se i >= argc: ERRO-falta parametro */
             trataNomeArquivo(arqquery,FILE_NAME_LEN,argv[i]);
         }
         i++;
     } //while

    strcat(dir,"/");strcat(dir,arq);
    strcat(dirsaida,"/arq.svg");

    FILE *arqgeo = fopen(dir, "r"); // exemplo.geo e retg-decres.geo
    FILE *arqnovo = fopen(dirsaida, "w+");
    Fila fila;
    fila = criafila(0);
    if (!arqgeo) {
        printf("Erro ao abrir o arquivo GEO  %s\n", dir);
        return 1;
    }
    fprintf(arqnovo, "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
    //fclose(arqnovo);
    do {
        z = fscanf(arqgeo, " %s", comando);
        if (z == 1) {
            //printf("li %s\n", comando);
        }
        else {
            break;
        }
        if (comando[0] == 'c') {
            fscanf(arqgeo, "%d %f %f %f %s %s", &i, &x, &y, &r, corb, corp);
            //printf("li %d %f %f %f %s %s\n", i, x, y, r, corb, corp);
            Ponto p = criaPonto(x, y);
            Circulo c = criaCirculo(p, r, corb, corp, i);
            adicionar(&fila, c, 0);
            //printCirculo(c);
        }
        if (comando[0] == 'r') {
            double rx, ry, rw, rh;
            fscanf(arqgeo, "%d %lf %lf %lf %lf %s %s", &i, &rx, &ry, &rw, &rh, corb, corp);
            Retangulo r = criaRetangulo(rx, ry, rw, rh, corb, corp, i);
            adicionar(&fila, r, 1);
            //printRetangulo(r);
        }
        if (comando[0] == 'l') {
            fscanf(arqgeo, "%d %f %f %f %f %s", &i, &x1, &y1, &x2, &y2, cor);
            Ponto p1, p2;
            p1 = criaPonto(x1, y1);
            p2 = criaPonto(x2, y2);
            Linha lin = criaLinha(p1, p2, cor, i);
            adicionar(&fila, lin, 2);
            //printf("li %d %f %f %f %f %s\n", i, x1, y1, x2, y2, cor);
        }
        if (comando[0] == 't') {
            if (comando[1] == 's') {
                fscanf(arqgeo, "%s %s %s", fFamily, fWeight, fSize);
                //printf("li %s %s %s\n", fFamily, fWeight, fSize);
            }
            else {
                fscanf(arqgeo, "%d %f %f %s %s %c", &i, &x, &y, corb, corp, &a);
                fgets(txto, sizeof(txto), arqgeo);
                //printf("li %d %f %f %s %s %c %s\n", i, x, y, corb, corp, a, txto);
                Ponto pt = criaPonto(x, y);
                Texto text = criaTexto(pt, corb, corp, txto, a, i);
                adicionar(&fila, text, 3);
            }
        }
    } while (z == 1);
    //arqnovo = fopen(arqnovo, "a+");

    //remover(&fila);
    exibirfila(fila, arqnovo);

    fprintf(arqnovo, "</svg>\n");
    fclose(arqgeo);
    fclose(arqnovo);
	printf("Arquivo SVG criado!\n");

    // Leitura do query
    
    strcat(bed,"/");strcat(bed,arqquery);
    strcat(dirsaidabase, "/arqquery.svg");
    FILE *fileq = fopen(bed, "r");
    if (!fileq) {
        printf("OCORREU UM ERRO AO LER O QUERY");
    }
    else {
        printf("QUERY LIDO!");
    }
    FILE *filesaidaquery = fopen(dirsaidabase, "w+");

	Disparador listadisp[100];
    Pilha listacarr[100];
    int tipo, j, n;
    int iesq, idir;

    Fila filasaida = criafila(0);

    do {
        z = fscanf(fileq, " %s", comando);
        if (z == 1) {
            printf("LIDO %s\n", comando);
        }
        else {
            break;
        }
        if (!strcmp(comando, "pd")) {
            fscanf(fileq, "%d %f %f", &i, &x, &y);
            Disparador disp;
            disp = criaDisparador(i, x, y); 
            listadisp[i] = disp;

            printf("Disparador %d criado!\n", iddisparador(listadisp[i]));
        }
        else if (!strcmp(comando, "lc")) {
            
            fscanf(fileq, "%d %d", &i, &n);
            printf("Inicializando carregador!\n");
            Pilha pilha = criapilha(0);
            Item item;
            for (j=0; j<n; j++) {
                item = remover(&fila, &tipo);
                empilha(&pilha, item, tipo);
            }
            printf("Pilha %d carregada!\n", i);
            listacarr[i] = pilha;
            //exibir(listacarr[i]);
        }
        else if (!strcmp(comando, "atch")) {
            
            fscanf(fileq, "%d %d %d", &i, &iesq, &idir);
            printf("Encaixando disparadores!\n");
            Disparador disp = listadisp[i];

            Pilha pilhaesq = listacarr[iesq];
            Pilha pilhadir = listacarr[idir];
            encaixar(disp, pilhaesq, pilhadir);
            printf("Encaixe realizado!\n");
        }
        else if (!strcmp(comando, "rjd")) {
            fscanf(fileq, "%f %f %f %f", &x1, &y1, &x2, &y2);
        }
        else if (!strcmp(comando, "shft")) {
            
            fscanf(fileq, "%i %c %i", &i, &a, &n);
            printf("REALIZANDO SHIFT\n");
            for (int j=0; j<n; j++) {
                 botao(listadisp[i], a);
            }
            printf("SHIFT REALIZADO PARA %c\n", a);
        }
        else if (!strcmp(comando, "dsp")) {
            double nx, ny;
            fscanf(fileq, "%i %lf %lf", &i, &nx, &ny);
            Disparador disp = listadisp[i];
            printf("Disparando um objeto: %d\n", tipoatualnodisparo(disp));
            adicionar(&filasaida, disparar(disp, nx, ny), tipoatualnodisparo(disp));
        }
        
    } while (z == 1);


    fprintf(filesaidaquery, "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
    exibirfila(filasaida, filesaidaquery);
    fprintf(filesaidaquery, "</svg>\n");
    fclose(filesaidaquery);
	printf("Fim do programa\n");


    return 0;
}