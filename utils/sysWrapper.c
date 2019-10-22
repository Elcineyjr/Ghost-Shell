#include "sysWrapper.h"

//checa se vetor de comandos deve ser chamado em background ou foreground
void exec(char** comandos){
    
    //seta o tratador de SIGINT dos filhos
    struct sigaction sigintH = {.sa_handler = SIG_IGN}; //SIG_IGN é o tratador padrão que ignora sinais
    if (sigemptyset(&sigintH.sa_mask) == -1 ||
        sigaction(SIGINT, &sigintH, NULL) == -1)
        perror("Falha ao definir novo handler para SIGINT");
    
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
    printf("\n");
    int status;

    char** comandos_args = quebraStringPorToken(comandos[0], " ");
        
    int f = fork_gs();

    if(f == 0){
        
	    // Faz a inicializacao correta das structs que definirao os novos handlers
        struct sigaction sigintH = {.sa_handler = SIG_IGN};
        if (sigemptyset(&sigintH.sa_mask) == -1 ||
            sigaction(SIGINT, &sigintH, NULL) == -1)
            perror("__msg de erro qnd falha__");

        
        execvp(comandos_args[0], comandos_args); 
    }

    waitpid(-1, &status, WNOHANG);
    libera_comandos(comandos_args);

    __gid_t grupo = f;// concerva o grupo para q que todos tenham o mesmo grupo

    for(int i = 1; i < 5; i++){
        if(!comandos[i]) break;

        char** comandos_args = quebraStringPorToken(comandos[i], " ");
        
        int f = fork_gs();

        if(f == 0){
            struct sigaction sigintH = {.sa_handler = SIG_IGN};
            if (sigemptyset(&sigintH.sa_mask) == -1 ||
                sigaction(SIGINT, &sigintH, NULL) == -1)
                    perror("__msg de erro qnd falha__");
            
            setpgid(0, grupo);//seta grupo da linha
            execvp(comandos_args[0], comandos_args); 
        }

        waitpid(-1, &status, WNOHANG); //permite que a shell continue executando outros comandos 

        libera_comandos(comandos_args);
    }
}