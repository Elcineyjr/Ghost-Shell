#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include "utils/stringHandler.h"
#include "utils/sysWrapper.h"
#include "utils/manipulaSinais.h"

#define QTD_TESTE 3 

//XXXXXTODO checar os grupos dos processos que estão sendo criados em background para saber se cada 
    //chamada conjunta está gerando um grupo distinto seguindo a especificação do trab

//XXXTODO testar bugs em comandos em background
    //XXXos processos estão exibindo saida

//TODO tratar sinais
    //Todos os processos filhos da gsh devem ignorar o comando Ctrl_C(SIGINT)
    //Crtl+Z deve deve suspender todos os processos filhos da shell, mas a shell deve continuar normal

//TODO Operações internas
    //mywait: libera todos os porcesos no estado Zombie(diretos e indiretos), descosiderando os ghosts
    //clean&die: mata a shell apos garantir que todos seus filhos(indiretos e diretos) já morreram (background e ghosts tambem) 

int main(int argc, char* argv[]){
    
    char* entrada = NULL;

    char** comandos;

    printf("Bem vindo a Ghost Shell!!\n");
    int i =0;
    while(i < QTD_TESTE){ //limita a quantidade de testes pra nao dar ctrl+c enquanto falta tratar sinal 
                          //mas nesse caso a shell morre após o terceiro loop do while
        printf("gsh> ");

        //caso erro na leitura da entrada volta pro inicio do loop
        if(!le_entrada(&entrada)) continue;
        
        //trata entrada para gerar comandos
        comandos = quebraStringPorToken(entrada, "#");

        //executa comandos lidos
        exec(comandos);
        sleep(1);// Para impedir que a saida de um comando (como o ls) se sobreponha ao gsh>
        printf("\n\n");//algumas vezes o "gsh" n estava aparecendo
        signal(SIGINT, trata_SIGINT);//coloquei aqui pois caso não haja filhos (comandos que foram chamados) não é necessário tratar o sinal SIGINT

        //libera memoria alocada 
        libera_comandos(comandos);
        free(entrada);
        
        i++;
    }
    
    return 0;
}
