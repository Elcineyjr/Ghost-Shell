#include "signalHandler.h"
#include "processList.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/resource.h>


//Caso a shell tenha filhos se deve perguntar se o usuário quer realmente fecha-la com o comando STGINT
void trata_SIGINT(int i){
    //caso exista algum filho da shell ainda vivo, deve-se confirmar com usuario se ele quer mesmo finalizar a shell
    if(!lista_vazia(lista_processos)){
        printf("\nA shell possui filhos, tem certeza que deseja encerrar sessão? S/N\n");
        char c = getchar();
        if(!(c == 'S' || c == 's')){
            return;
            //printf("Finalizando!\n");
            // cleanEdie(); //TODO tem q dar um clean&die ou é pra finalizar a shell e deixar todos os filhos pra tras?
            //exit(0);
        }
    }
    signal(SIGINT, SIG_DFL);
    raise(SIGINT);
    
}

//suspende todos os processos (foreground, background e ghosts) menos a propria shell
void trata_SIGTSTP(int i){
    printf("\nSuspendendo todos os filhos.\n");
    
    suspende_processos(lista_processos);

    raise(SIGCONT);
}


void trata_SIGCHLD(int i){
    int gid =  get_process_SIGCHLD(lista_processos);
    //printf("grupo: %d",gid);
    mata_todos_do_grupo(lista_processos, gid);    
    //signal(SIGCHLD,SIG_DFL);
    //raise(SIGCHLD);
}