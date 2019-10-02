#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

char** comandos;

void trataEntrada(char* entrada);
char* remove_spaces(char* s);

int main(int argc, char* argv[]){

    comandos = malloc(5 * sizeof(char*)); //vetor de comandos lidos de stdin

    char* entrada = NULL;
    size_t buffer_size;

    printf("Bem vindo ao Ghost Shell!!\n");
    while(1){
        printf("gsh> ");
        getline(&entrada, &buffer_size, stdin);
        printf("entrada lida: %s\n", entrada);
        
        trataEntrada(entrada);

        // for(int i = 0; i < 5;i++){
        //     if(comandos[i]) execlp()
        // }

        printf("comandos guardados no vetor: ");
        for(int i = 0; i<5; i++)
            if(comandos[i]) printf("%s, " ,comandos[i]);

        printf("\n");
        

        //libera memoria alocada
        free(entrada);
        for(int i = 0; i<5; i++)
            if(comandos[i]) free(comandos[i]);
        free(comandos);

        break;
    }

    return 0;
}


// Tratador de entrada
void trataEntrada(char* entrada){
    int j = 0; //contador de comandos lidos
    int tam_entrada = strlen(entrada)+1;

    //copia entrada para nova variavel para quebra-la em tokens
    char* cpy_entrada = malloc(sizeof(char) * tam_entrada);
    strcpy(cpy_entrada, entrada);

    char* token = strtok(cpy_entrada, "#\n"); //le o primeiro comando da linha
    for(int i = 0; i < 5; i++){     
        if(!token) break; //se nao tiver comandos ou leu a linha toda, para de ler novos comandos
        
        //aloca e copia o token lido para a string alocada
        int tam_token = strlen(token)+1;
        char* novo_comando = malloc(sizeof(char) * tam_token);
        strcpy(novo_comando, token);

        comandos[i] = novo_comando; //adiciona comando a lista de comandos

        token = strtok(NULL, "#\n"); //le o proximo comando
    }

    free(cpy_entrada);
}


//remove todos os espaços de uma string
char* remove_spaces(char* s) {
    const char* d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while (*s++ = *d++);
    
    return s;
}