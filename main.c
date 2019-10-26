#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>


#include "utils/stringHandler.h"
#include "utils/sysWrapper.h"
#include "utils/listas.h"
#include "utils/signalHandler.h"

#define QTD_TESTE 10 


int main(int argc, char* argv[]){
    srand((unsigned) time(NULL));

    printf("Bem vindo a Ghost Shell!!\n");

    //inicializa listas 
    // inicializa_filhos(); //inicializa vetor que guarda filhos da shell

    char* entrada = NULL;
    char** comandos;
    
    // Instala os novos handlers de sinal
    struct sigaction handler_sigint = {.sa_handler = trata_SIGINT};
    struct sigaction handler_sigtstp = {.sa_handler = suspende_filhos}; //TODO mudar nome da funçao


    //novo handler do sinal SIGTSTP  (ctrl+Z)
    if (sigemptyset(&handler_sigtstp.sa_mask) == -1 ||
        sigaction(SIGTSTP, &handler_sigtstp, NULL) == -1)
        perror("Falha ao definir novo handler para SIGTSTP\n"); 

    //novo handler do sinal SIGINT   (ctrl+C)
    if (sigemptyset(&handler_sigint.sa_mask) == -1 ||
        sigaction(SIGINT, &handler_sigint, NULL) == -1)
            perror("Falha ao definir novo handler para SIGINT");


    int i = 0;
    while(i < QTD_TESTE){ //limita a quantidade de testes 
        printf("gsh> ");

        //caso erro na leitura da entrada volta pro inicio do loop
        if (!le_entrada(&entrada)) continue;

        //verifica se usuario digitou um comando interno ou externo e o executa
        int flag = eh_comando_interno(entrada);
        if(flag){
            roda_comando_interno(flag); //TODO pensar no clean&die, pq tem q liberar a memoria da entrada lida
        }else{
            //trata entrada para gerar comandos
            comandos = quebraStringPorToken(entrada, "#");

            exec(comandos);
            
            //libera o vetor de comandos da entrada
            libera_comandos(comandos);
        }

        //libera memoria alocada pra entrada 
        free(entrada);
        i++;
    }

    return 0;
}


