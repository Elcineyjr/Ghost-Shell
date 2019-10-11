#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "utils/stringHandler.h"
#include "utils/sysWrapper.h"

#define QTD_TESTE 3 

//TODO testar bugs em comandos em background
//TODO tratar sinais

int main(int argc, char* argv[]){
    char* entrada = NULL;

    char** comandos;

    printf("Bem vindo a Ghost Shell!!\n");
    int i =0;
    while(i < QTD_TESTE){ //limita a quantidade de testes pra nao dar ctrl+c enquanto falta tratar sinal
        printf("gsh> ");

        //caso erro na leitura da entrada volta pro inicio do loop
        if(!le_entrada(&entrada)) continue;
        
        //trata entrada para gerar comandos
        comandos = quebraStringPorToken(entrada, "#");

        //executa comandos lidos
        exec(comandos);

        //libera memoria alocada 
        libera_comandos(comandos);
        free(entrada);
        
        i++;
    }
    
    return 0;
}
