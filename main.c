#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

#include "utils/stringHandler.h"
#include "utils/sysWrapper.h"
#include "utils/listas.h"
#include "utils/sinais.h"

#define QTD_TESTE 3 

void loop_shell();

int main(int argc, char* argv[]){
    printf("Pid da shell - %d\n", getpid());
    printf("Bem vindo a Ghost Shell!!\n");
    loop_shell();

    return 0;
}

//acho que modularizei de mais
void loop_shell(){
    //inicializa listas 
    inicializa_filhos(); //inicializa vetor que guarda filhos da shell

    // Inicializacao do input e declaracao do tamanho do buffer dele (explicacao para os valores declarados na hora de ler o stdin)
    char* entrada = NULL;
    char** comandos;
    int i =0;
    
    // Instala o novo handler para o sinal SIGINT
    struct sigaction sigintH = {.sa_handler = trata_SIGINT};

    //Instala o novo handler para o sinal SIGTSTP
    struct sigaction sigtstpH = {.sa_handler = suspende_filhos};
    if (sigemptyset(&sigtstpH.sa_mask) == -1 ||//seta a mascara de sinais bloqueados como vazia
        sigaction(SIGTSTP, &sigtstpH, NULL) == -1) // seta o novo tratador de sinal
        perror("Falha ao definir novo handler para SIGTSTP\n");//se algum deles falhar printa essa mensagem

    while(i < QTD_TESTE){ //limita a quantidade de testes pra nao dar ctrl+c enquanto falta tratar sinal 
                          //mas nesse caso a shell morre após o terceiro loop do while
        
        //Como o tratador de SIGINT muda apos a chamada da função exec(),
        //é preciso resetalo para o comportamento proprio da shell
        if (sigemptyset(&sigintH.sa_mask) == -1 ||
            sigaction(SIGINT, &sigintH, NULL) == -1)
                perror("Falha ao definir novo handler para SIGINT");
        
        printf("gsh> ");

        //caso erro na leitura da entrada volta pro inicio do loop
        if (!le_entrada(&entrada)){ 
            printf("\e[H\e[2J"); //limpa a tela (não sei como funciona, mas funciona)
            continue;
        }

        //executa comando interno mywait
        if(!strcmp(entrada, "mywait")){
            mywait();
            continue;
        }

        //executa comando interno clean&die
        if(!strcmp(entrada, "clean&die")){
            printf("vc esta na cleanEdie\n"); 
            cleanEdie();
            continue;
        }

        //trata entrada para gerar comandos
        comandos = quebraStringPorToken(entrada, "#");
        printf("%s\n", comandos[0]);
        exec(comandos);
        
        sleep(1);// Para impedir que a saida de um comando (como o ls) se sobreponha ao gsh>

        //libera memoria alocada 
        libera_comandos(comandos);
        free(entrada);
        i++;
    }

}
