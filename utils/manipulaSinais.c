#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

//tratador de sinal
void trata_SIGINT(){
    char resposta;
    sigset_t blockmask;
    sigfillset(&blockmask);
    sigset_t oldset;
    sigprocmask(SIG_SETMASK, &blockmask, &oldset);
    printf("%d\n",sigismember(&blockmask, 9));

    printf("\nA shell possui filhos, tem certeza que deseja encerrar sessão? S/N\n");
    scanf("%c",&resposta);
    if(resposta == 'S'){
        printf("Shell finalizada\n");
        exit(0);
    }else if(resposta == 'N'){
        sigprocmask(SIG_SETMASK, &blockmask, &oldset);
        printf("\ngsh> ");
    }
}