#include "sysWrapper.h"

#define MY_WAIT 1
#define CLEAN_DIE 2

//verifica se entrada do usuario é um comando interno
int eh_comando_interno(char* string){
    if(!strcmp(string, "mywait"))   return MY_WAIT;
    if(!strcmp(string, "clean&die"))    return CLEAN_DIE;

    return 0;
}


//roda o comando interno recebido
void roda_comando_interno(int comando){
    if(comando == MY_WAIT){
        printf("finge que rodou mywait\n");
        // mywait();
    }else{
        printf("finge que rodou clean&die\n");
        // cleanEdie();
    }
}


//função para decidir se certo processo deve gerar um ghost ou nao (50% de chances)
int gerarGhost(){
	return (rand() % 2);
}


//checa se vetor de comandos deve ser chamado em background ou foreground
void exec(char** comandos){
    if(!comandos[1]){
        execForeground(comandos);
    }else{
        execBackground(comandos);
    }
}


//executa o comando passado em foreground
void execForeground(char** comandos){
    int status;

    //quebra a string de comandos por ' ' para separar as flags passadas no comando 
    char** comandos_args = quebraStringPorToken(comandos[0], " ");

    //gera filho pra executar o comando
    int f = fork(); 

    if (f == -1){ //checa falha no fork 
        printf("Falha no fork em foreground.\n");
        libera_comandos(comandos_args);
        return;
    } 

    //codigo de execução do filho da shell
    if(f == 0){
        //seta o tratador de SIGINT do filho para ignorar o sinal
        struct sigaction handler_filho_sigint = {.sa_handler = SIG_IGN}; 
        if (sigemptyset(&handler_filho_sigint.sa_mask) == -1 ||
            sigaction(SIGINT, &handler_filho_sigint, NULL) == -1)
            perror("Falha ao definir novo handler para SIGINT nos processos filhos.\n");

        //executa comando 
        if(execvp(comandos_args[0], comandos_args) == -1){
            printf("%s: command not found\n", comandos_args[0]);
            exit(CMD_NOT_FOUND_ERROR);
        }
    }
    
    //TODO adicionar na lista de processos rodando

    //shell espera filho finalizar
    waitpid(f, &status, 0);

    //libera vetor alocado pro comando e suas flags
    libera_comandos(comandos_args);
}


//executa a lista de comandos passados em background                //TODO ver se ta td no msm grupo e tratador de sinais
void execBackground(char** comandos){
    int status;
    int status2;

    //variavel a guardar o id do grupo
    __gid_t grupo;

    //itera toda a lista de comandos
    for(int i = 0; i < 5; i++){
        if(!comandos[i]) break;

        //quebra a string de comandos por ' ' para separar as flags passadas no comando 
        char** comandos_args = quebraStringPorToken(comandos[i], " ");
        
        //gera filho pra rodar o comando
        int f = fork();
         
        if(f == -1){ //checa erro no fork
            printf("Falha no fork em backgroung.\n");
            libera_comandos(comandos_args);
            return;
        }

        if(i == 0) grupo = f; //shell guarda o pid do primeiro comando para add os outros processos no mesmo group

        //codigo do processo filho
        if(f == 0){
            //seta o tratador de SIGINT dos filhos em bg para ignorar o sinal
            struct sigaction handler_sigint = {.sa_handler = SIG_IGN};
            if (sigemptyset(&handler_sigint.sa_mask) == -1 ||
                sigaction(SIGINT, &handler_sigint, NULL) == -1)
                perror("Falha ao definir novo handler para SIGINT nos processos background.\n");

            if(i == 0)
                setpgid(0,0);  //seta o id do grupo igual ao pid do primeiro comando a ser executado em bg
            else
                setpgid(0, grupo); //caso nao seja o primeiro comando, entao entra no mesmo grupo do primeiro comando


            int ghost = -1;
            if(gerarGhost()){ //caso filho deva gerar um ghost
                
                ghost = fork();

                //checa falha no fork 
                if (ghost == -1)
                    printf("Falha no fork do ghost.\n");
                else{
                    
                    if(ghost == 0){ //codigo a ser executado pelo ghost

                        //coloca o ghost no mesmo grupo q seu pai
                        setpgid(0, __getpgid(getppid()));

                        //ghost executa mesmo comando do seu pai
                        if(execvp(comandos_args[0], comandos_args) == -1){
                            printf("%s: command not found\n", comandos_args[0]);
                            exit(CMD_NOT_FOUND_ERROR);
                        }
                    }else{ //codigo q o processo pai executa (precisa disso?)
                        //TODO add ghost na lista de ghost e tudo mais (cuidado pois ghost pode ta setado como -1 por erro no fork)

                    }
                }
            }

            //processo filho nao espera o ghost caso tenha sido criado
            waitpid(-1, &status2, WNOHANG); 

            //filho executa comando 
            if(execvp(comandos_args[0], comandos_args) == -1){
                printf("%s: command not found\n", comandos_args[0]);
                exit(CMD_NOT_FOUND_ERROR);
            } 
        }

        //shell nao espera filho criado 
        waitpid(-1, &status, WNOHANG); 

        //libera vetor alocado pro comando e suas flags
        libera_comandos(comandos_args);
        // sleep(1);
        // printf("gsh> ");
    }
}