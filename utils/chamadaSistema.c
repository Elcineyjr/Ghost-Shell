#include "chamadaSistema.h"
#include "tratadorString.h"

void exec(char*** comandos){
    adicionaCaminho(comandos);

    if(!comandos[1])
        execForeground(comandos[0]); //executa em foreground pois foi passado apenas um comando na shell
    else
        execBackground(comandos); //executa grupo em backgound pois foi passado uma sequencia de comandos na shell

    //liberaComandos(); //TODO
}


//chama o arquivo executavel do comando passado na shell (TODO tratar o ctrl+c)
void execForeground(char** comando){
    if(comando){
        int f = fork();
        if(f == 0){
            char *argv[]={comando[0], comando[1], comando[2], comando[3], comando[4], NULL};
            char *env_args[] = {"PATH=/bin", (char*)0};
            execve(argv[0],argv,env_args);    
        }
        wait();
    }
}


//cria um grupo com todos os comandos passados e roda esse grupo em background
void execBackground(char*** comandos){
    printf("finge q ta funcionando\n");
}