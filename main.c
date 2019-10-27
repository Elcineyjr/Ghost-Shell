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
#include "utils/signalHandler.h"
#include "utils/processList.h"
#include "utils/internalCommands.h"

#define QTD_TESTE 10 




int main(int argc, char* argv[]){
    srand((unsigned) time(NULL));

    printf("Bem vindo a Ghost Shell!!\n");

    //inicializa listas 
    lista_processos = cria_lista();

    char* entrada = NULL;
    char** comandos;
    
    // Instala os novos handlers de sinal
    struct sigaction handler_sigint = {.sa_handler = trata_SIGINT};
    struct sigaction handler_sigtstp = {.sa_handler = trata_SIGTSTP};


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
            roda_comando_interno(flag);
            
            if(flag == CLEAN_DIE){
                free(entrada);
                break; //clean&die nao da exit pq tem q liberar a memoria 
            }
        }else{
            //trata entrada para gerar comandos
            comandos = quebraStringPorToken(entrada, "#");

            exec(comandos);
            
            //libera o vetor de comandos da entrada
            libera_comandos(comandos);
        }

        sleep(1); //TODO eu acho isso feio, pode dar a impressao q o programa ta lento

        //libera memoria alocada pra entrada 
        free(entrada);
        i++;
    }

    libera_lista(lista_processos);

    return 0;
}


