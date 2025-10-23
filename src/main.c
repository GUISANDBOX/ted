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
#include "comandosgeo.h" 
#include "comandosqry.h"

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
    
    while (i < argc){
         if (strcmp(argv[i],"-e")==0){
             i++;
             /* se i >= argc: ERRO-falta parametro */
             trataPath(dir,PATH_LEN, argv[i]);
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
    
    fila=processaGeo(arqgeo, fila, arqnovo);

    fclose(arqgeo);
    fclose(arqnovo);
    printf("Arquivo SVG criado!\n");

    strcat(bed,"/");strcat(bed,arqquery);
    strcat(dirsaidabase, "/arqquery.svg");
    FILE *fileq = fopen(bed, "r");
    if (!fileq) {
        printf("OCORREU UM ERRO AO LER O QUERY\n");
        return 1;
    }
    FILE *filesaidaquery = fopen(dirsaidabase, "w+");
    Fila filasaida = criafila(0);
    processaQry(fileq, filasaida, filesaidaquery, fila);

    fclose(fileq);
    fclose(filesaidaquery);
    printf("Sucesso!\n");

    return 0;
}