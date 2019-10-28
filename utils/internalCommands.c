#include "internalCommands.h"
#include "processList.h"
#include "signalHandler.h"


//mywait
void mywait_(){
    int pid = 1;
    int status;
    limpa_lista(lista_processos);
    while(pid > 0){
        pid = waitpid(-1, &status, WNOHANG);        
        if(kill(SIGKILL, pid)){
            Process* p = retira_processo(lista_processos,pid);
            libera_processo(p);
        }
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
    if(!strcmp(string, "printme"))    return PRINTME;
    return 0;
}

 void process_printme(){
     printa_lista(lista_processos);
 }


//roda o comando interno recebido
void roda_comando_interno(int comando){
    if(comando == MY_WAIT)
        mywait_();
    else if (comando == PRINTME)
        process_printme();
    else
        cleanEdie_();
}