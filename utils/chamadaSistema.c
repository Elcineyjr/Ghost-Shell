#include "chamadaSistema.h"
#include "tratadorString.h"

//chama o arquivo executavel de cada comando (TODO criar processos para entao dar o exec)
void resolveComandos(char*** comandos){

    adicionaCaminho(comandos);
    for(int i = 0; i < 5; i++){
        if(!comandos[i]) break;
        char *argv[]={comandos[i][0], comandos[i][1], comandos[i][2], comandos[i][3], comandos[i][4], NULL};
        char *env_args[] = {"PATH=/bin", (char*)0};
        execve(argv[0],argv,env_args);    
    }
}