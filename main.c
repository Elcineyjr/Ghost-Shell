#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "utils/tratadorString.h"
#include "utils/chamadaSistema.h"

int main(int argc, char* argv[]){

    char* entrada = NULL;
    size_t buffer_size;
    char** comandosTok; //token de comandos lidos de stdin, ainda sem tratamento de parametros
    char*** comandosArgs; //vetor de comandos, sendo cada indice um vetor contendo o comando e seus parametros 

    // system("clear"); //comentar essa linha caso rodar valgrind, pq pode bugar a visualizacao
    printf("Bem vindo ao Ghost Shell!!\n");
    while(1){
        printf("gsh> ");
        getline(&entrada, &buffer_size, stdin);
        
        //quebra a linha de entrada em comandos, separados pelo '#', porem nao trata
        //os espacos entre os parametros do comando 
        comandosTok = trataStringPorToken(entrada, "#\n");

        //caso exista espacos na string de comando significa q tal comando possui parametros,
        //assim transforma a lista de comandos em uma matriz de comandos e parametros
        comandosArgs = malloc(5 * sizeof(char**));
        for(int i = 0; i<5; i++){
            if(comandosTok[i]){
               comandosArgs[i] = trataStringPorToken(comandosTok[i], " ");
            }
        }

        exec(comandosArgs);

        // break;

    }
    

    //libera memoria alocada (TODO deixar isso menos feio)
    free(entrada);
    for(int i = 0; i<5; i++)
        if(comandosTok[i]) free(comandosTok[i]);
    free(comandosTok);

    for(int i = 0; i<5; i++){
        for(int j = 0; j < 5; j++)
            if(comandosArgs[i]) free(comandosArgs[i][j]);
        free(comandosArgs[i]);
    }
    
    free(comandosArgs);

    return 0;
}
