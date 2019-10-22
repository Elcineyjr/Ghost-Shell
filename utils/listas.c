#include "listas.h"


void inicializa_filhos(){
    filhos = calloc(maxFilhos, sizeof(__pid_t) );
}

//adiciona pid
void addFilho(__pid_t pid){
    for(int i = 0; i < maxFilhos; i++){
        if(filhos[i] == 0){ 
            filhos[i] = pid;
            return;
        }
    }

    printf("Número max de filhos criados.\n");
}

//testa lista de pids
int tem_filho(){
    for(int i = 0; i < maxFilhos; i++){
        if(filhos[i] != 0) return 1;
    }
    return 0;
}

//Para filhos e ghosts, os print são so para testes
void para_filhos_e_Ghosts(){
    for(int i = 0; i < maxFilhos; i++){
        if( filhos[i] != 0 ) {
            if( killpg(filhos[i], SIGTSTP) )//envia sinal para o grupo
                printf("deu ruim na hora de parar os filhos - %d\n", filhos[i]);//acredito que erros nesse print sejam de processos que já estão mortos de um dado grupo, logo n podem ser pausados
            else
                printf("parou com sucesso - pid %d  \n", filhos[i]);
        }
    }

}

/*clean&die: deve terminar a operação da shell, mas antes, esta deve garantir que todos os
seus descendentes vivos morram também (background e ghosts!)... Ela só deve morrer após
todos eles (herdeiros diretos e indiretos) terem morrido*/
void cleanEdie(){
    for(int i = 0; i < maxFilhos; i++){
        if( filhos[i] != 0 ) {
            if( killpg(filhos[i], SIGKILL) )
                printf("deu ruim na hora de mata os filho - %d\n", filhos[i]);//acredito que os erros nesse print sejam de processos que já estão mortos, logo n podem ser mortos de novo
            else
                printf("mato com sucesso - %d\n", filhos[i]); 
        }
    }

    printf("Shell finalizada\n");
    exit(0);
}

/*mywait: faz com que a shell libere todos os seus descendentes (diretos e indiretos) que
estejam no estado “Zombie” antes de exibir um novo prompt Aqui vocês podem
desconsiderar os processos ghosts… afinal o cara já era ghost mesmo… que mal tem ele se
tornar um Zombie e ficar perambulando por ahi !?
*/
void mywait(){
    __pid_t pid = 0, status;

    while(pid != -1) {
        pid = waitpid(-1, &status, WNOHANG);//a ideia é a cada loop o waitpid retorne um ip de um processo zumbi
        kill(SIGKILL, pid);
        printf("Pid - %d\n", pid);//somente para testes
    }

}