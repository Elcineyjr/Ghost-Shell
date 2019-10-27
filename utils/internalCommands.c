#include <string.h>
#include <stdio.h>
#include <wait.h>

#include "internalCommands.h"
#include "processList.h"


//mywait
void mywait_(){
    int pid = 0;
    int status;

    while(pid != -1){   //TODO sempre fica com pid = 0 e nao sai do loop
        pid = waitpid(-1, &status, WNOHANG);    
        kill(SIGKILL, pid);
        printf("pid: %d\n", pid);
    }
    printf("filhos zombies coletados!!\n");
}


//clean and die
void cleanEdie_(){
    if(!lista_processos) return;

    Process* aux = get_lista_prim(lista_processos);
    while(aux){
        int gid_ = get_processo_GID(aux);
        
        mata_todos_do_grupo(lista_processos, gid_);

        aux = get_lista_prim(lista_processos);
    }
    printf("Shell finalizada!\n");
}



//verifica se entrada do usuario é um comando interno
int eh_comando_interno(char* string){
    if(!strcmp(string, "mywait"))   return MY_WAIT;
    if(!strcmp(string, "clean&die"))    return CLEAN_DIE;

    return 0;
}


//roda o comando interno recebido
void roda_comando_interno(int comando){
    if(comando == MY_WAIT)
        mywait_();
    else
        cleanEdie_();
}