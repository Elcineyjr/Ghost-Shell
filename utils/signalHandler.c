#include "signalHandler.h"
#include "processList.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/resource.h>


//Caso a shell tenha filhos se deve perguntar se o usuário quer realmente fecha-la com o comando STGINT
void trata_SIGINT(int i){
    //caso exista algum filho da shell ainda vivo, deve-se confirmar com usuario se ele quer mesmo finalizar a shell
    limpa_lista(lista_processos);
    if(!lista_vazia(lista_processos)){
        printf("\nA shell possui filhos, tem certeza que deseja encerrar sessão? S/N\n");
        char c = getchar();
        if(!(c == 'S' || c == 's')){
            return;            
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

// mata processos com mesmo pgid de um processo morto por um sinal
void trata_SIGCHLD(int i){
    //printf("%d\n",i);
    int gid = get_process_SIGCHLD(lista_processos);
    //printf("%d",gid);
    if(gid != -1) mata_todos_do_grupo(lista_processos, gid);
    //raise(SIGCHLD);
}
// Verifica qual processo filho morreu, pega seu pgdid, e retorna para a função trata_SIGCHLD
int get_process_SIGCHLD(){
    siginfo_t status;
    int id = waitid(P_ALL, 0, &status, WNOWAIT | WNOHANG | WEXITED);
    //printf("status.si_pid = %d status.si_code = %d id = %d\n",status.si_pid,status.si_code,id);
    if (status.si_pid > 0 && status.si_code == CLD_KILLED && id == 0) {
        int gid = getpgid(status.si_pid);
        waitpid(status.si_pid, NULL, WNOHANG);
        return gid;
    }
    return -1;
}