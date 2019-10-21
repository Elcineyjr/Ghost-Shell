#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include "utils/stringHandler.h"
#include "utils/sysWrapper.h"

#define QTD_TESTE 3 

//XXXXXTODO checar os grupos dos processos que estão sendo criados em background para saber se cada 
    //chamada conjunta está gerando um grupo distinto seguindo a especificação do trab

//XXXTODO testar bugs em comandos em background
    //XXXos processos estão exibindo saida

//TODO tratar sinais
    //XXXXXXXTodos os processos filhos da gsh devem ignorar o comando Ctrl_C(SIGINT)
    //XXXXXXXCrtl+Z(SIGTSTP) deve deve suspender todos os processos filhos da shell, mas a shell deve continuar normal

//TODO Operações internas
    //mywait: libera todos os procesos no estado Zombie(diretos e indiretos), descosiderando os ghosts // deve ter algum sinal que processos dão quando viram zumbis, acho que se a gente por um tratador disso a gente consegue tratar.
    //SIGCHLD - https://vitux.com/how-to-kill-zombie-processes-in-ubuntu-18-04/
    //clean&die: mata a shell apos garantir que todos seus filhos(indiretos e diretos) já morreram (background e ghosts tambem) //se eu matar todos os processos de todos os grupos isso deveria funcionar né?


void loop_shell();

void trata_SIGINT(int i){
    printf("\n");
    if( tem_filho() ){
        printf("\nA shell possui filhos, tem certeza que deseja encerrar sessão? S/N\n");
        if(getchar() == 'S'){
            mata_filhos();
            printf("Shell finalizada\n");
            exit(0);
        }
        return;
    }
    
    exit(0);
}

//suspende todos os processos (foreground, background e ghosts)
void suspende_filhos(int i){
    printf("\nSuspendendo todos os filhos.\n");
    para_filhos_e_Ghosts();
    return;
}



int main(int argc, char* argv[]){
    printf("Bem vindo a Ghost Shell!!\n");
    loop_shell();

    return 0;
}

void loop_shell(){
    printf("eu sou o %d\n", getpid());
    //inicializa listas 
    inicializa_filhos();

    // Inicializacao do input e declaracao do tamanho do buffer dele (explicacao para os valores declarados na hora de ler o stdin)
    char* entrada = NULL;
    char** comandos;
    int i =0;
    
    // Instala o novo handler para o sinal SIGINT
    struct sigaction sigintH = {.sa_handler = trata_SIGINT};

    struct sigaction sigtstpH = {.sa_handler = suspende_filhos};
    if (sigemptyset(&sigtstpH.sa_mask) == -1 ||
        sigaction(SIGTSTP, &sigtstpH, NULL) == -1)
        perror("Falha ao definir novo handler para SIGTSTP\n");

    while(i < QTD_TESTE){ //limita a quantidade de testes pra nao dar ctrl+c enquanto falta tratar sinal 
                          //mas nesse caso a shell morre após o terceiro loop do while
        if (sigemptyset(&sigintH.sa_mask) == -1 ||
            sigaction(SIGINT, &sigintH, NULL) == -1)
                perror("Falha ao definir novo handler para SIGINT");
        
        printf("gsh> ");

        //caso erro na leitura da entrada volta pro inicio do loop
        //if(!le_entrada(&entrada)) continue;
        if (!le_entrada(&entrada)){ 
            printf("\e[H\e[2J");
            continue;}

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
