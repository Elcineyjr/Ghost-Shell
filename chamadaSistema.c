#include "chamadaSistema.h"

void resolveComandos(char** comandos){
    printf("%s",comandos[0]);
    char *argv[]={comandos[0],NULL};
    char *env_args[] = {"PATH=/bin", (char*)0};
    execve(argv[0],argv,env_args);    
}