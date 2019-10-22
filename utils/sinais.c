#include "sinais.h"


//Caso a shell tenha filhos se deve perguntar se o usuário quer realmente fecha-la com o comando STGINT
void trata_SIGINT(int i){
    printf("\n");
    if( tem_filho() ){ //checa se tem filho
        printf("\nA shell possui filhos, tem certeza que deseja encerrar sessão? S/N\n");
        if(getchar() == 'S'){
            cleanEdie(); 
            exit(0);
        }
        return;
    }
    
    exit(0);
}

//suspende todos os processos (foreground, background e ghosts) menos a propria shell
void suspende_filhos(int i){
    printf("\nSuspendendo todos os filhos.\n");
    para_filhos_e_Ghosts();
    return;
}