#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

char* comandos[5];

char** tratarEntrada(char* entrada);
char* remove_spaces(char* s);

int main(int argc, char* argv[]){
    
    char* entrada;
    char** comandos;

    printf("Bem vindo ao Ghost Shell!!\n");
    while(1){
        printf("gsh> ");
        scanf("%s", entrada);
        printf("discord é uma merda\n");
        comandos = tratarEntrada(entrada);

        for(int i = 0; i<5; i++){
            printf("%s, " ,comandos[i]);
        }
        printf("\n");
        break;
    }

    return 0;
}

// Tratador de entrada
char** tratarEntrada(char* entrada){
     //acho q tem q dar malloc    
    int j = 0; //contador de comandos lidos

    char* novo_comando = "CLEITON";
    char test[99];
    printf("novo comando: %s\n", novo_comando);
    printf("bbbbbbbbbbbbbbbbb\n");
    for(int i = 0; i < strlen(entrada)+1; i++){ 
        if(entrada[i] != '#' && entrada[i] != '\0'){
            printf("ccccccccccccccccc\n");
            strncat(novo_comando, entrada[i], 1); //concatena cada caracter q n eh # ou \0
//melhor a gente continuar amanha no lab então, pq ta foda mo sono aqui tb ja qual o comando pra mandar pro git?             
            printf("novo comando: %s\n", novo_comando);
            novo_comando = remove_spaces(novo_comando); //TODO tratar caso q comando tem argumentos
        }else{
            comandos[j] = novo_comando; //adiciona comando no vetor de comandos
            novo_comando = ""; //limpa a string pra ler outro comando
        }
    }

    return comandos;
}

char* remove_spaces(char* s) {
    const char* d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while (*s++ = *d++);
    
    printf("Discord é um merda\n");
    return s;
}

//