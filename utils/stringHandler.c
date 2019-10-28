#include "stringHandler.h"


int le_entrada(char** input){
    size_t buffSize = 0;
    
    //checa se usuario digitou pelo menos um caracter 
    int line;
    if ((line = getline(input, &buffSize, stdin)) > 1){

        int pos = strlen(*input) - 1;
        (*input)[pos] = '\0'; //substitui o '\n' por um '\0'

        rewind(stdin);
        return 1;
    }

    free(*input); 
    rewind(stdin); //caso ocorra erro na leitura limpa o buffer
    return 0;
}

// int getSetas(char** input){

// }


//quebra a string dada de a acordo com o token
char** quebraStringPorToken(char* input, const char* token){
    char** arr = malloc(5 * sizeof(char*)); // como o número máximo de argumentos especificados no trab é 3, aqui 
    //deveria ser 4, n? 1 para o comando, e 3 para os argumentos

    char* str = strtok(input, token); //le primeira string ate token
    for(int i = 0; i < 5; i++){
        if(!str){
            arr[i] = NULL; //caso nao tenha token
            break;
        } 

        //faz a posicao i do array apontar para string alocada 
        int tam_str = strlen(str)+1;
        arr[i] = malloc(tam_str* sizeof(char));
        strcpy(arr[i], str);

        //le a prox string ate o token
        str = strtok(NULL, token);
    }

    return arr;
}


//libera vetor de comandos
void libera_comandos(char** comandos){
    for(int i = 0; i < 5 && comandos[i]; i++)
        free(comandos[i]);
    free(comandos);
}

//remove espacos no inicio da string
char *ltrim(char *s){
    while(isspace(*s)) s++;
    return s;
}


//remove espacos no final da string
char *rtrim(char *s){
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

//remove espacos no inicio e final da string
char *trim(char *s){
    return rtrim(ltrim(s)); 
}