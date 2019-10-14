#include "sysWrapper.h"
#include "stringHandler.h"
#include "ghost.h"

//checa se vetor de comandos deve ser chamado em background ou foreground
void exec(char** comandos){
    if(!comandos[1]){
        execForeground(comandos);
    }else{
        execBackground(comandos);
    }
}


//
void execForeground(char** comandos){
    
    //quebra a string de comandos por ' ' para separar as flags passadas no comando 
    char** comandos_args = quebraStringPorToken(comandos[0], " ");
    
    int f = fork_gs();

    if(f == 0)
        execvp(comandos_args[0], comandos_args); 

    wait(NULL);

    libera_comandos(comandos_args);
}

void execBackground(char** comandos){
    int status;
    for(int i = 0; i < 5; i++){
        if(!comandos[i]) break;

        char** comandos_args = quebraStringPorToken(comandos[i], " ");
    
        int f = fork_gs();

        if(f == 0)
            execvp(comandos_args[0], comandos_args); 

        waitpid(-1, &status, WNOHANG);

        libera_comandos(comandos_args);
    }
}