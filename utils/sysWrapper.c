#include "sysWrapper.h"


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
        //seta o tratador de SIGINT do processo foreground para ignorar o sinal
        struct sigaction handler_filho_sigint = {.sa_handler = SIG_IGN}; 
        if (sigemptyset(&handler_filho_sigint.sa_mask) == -1 ||
            sigaction(SIGINT, &handler_filho_sigint, NULL) == -1)
            perror("Falha ao definir novo handler para SIGINT do processo foreground.\n");

        //executa comando 
        if(execvp(comandos_args[0], comandos_args) == -1){
            printf("%s: command not found\n", comandos_args[0]);
            exit(CMD_NOT_FOUND_ERROR);
        }
    }
    
    //insere o processo foreground na lista de processos vivos
    Process* p = cria_processo(f,f,0);
    insere(lista_processos, p);

    //shell espera filho finalizar
    waitpid(f, &status, 0);

    //remove o processo q era foreground da lista de processos vivos, dado q ele foi waitado
    Process* p1 = retira_processo(lista_processos, f);
    if(p1) libera_processo(p1); //libera memoria alocada 

    //libera vetor alocado pro comando e suas flags
    libera_comandos(comandos_args);
}


//executa a lista de comandos passados em background
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

        //adiciona o processo criado na lista de processos vivos
        Process* processo = cria_processo(f, grupo, 0);
        insere(lista_processos, processo);

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
            int random = gerarGhost();
            if(random){ //caso filho deva gerar um ghost
                
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

        // sleep(1);

        //shell nao espera filho criado 
        waitpid(-1, &status, WNOHANG); 

        //libera vetor alocado pro comando e suas flags
        libera_comandos(comandos_args);
    }
}