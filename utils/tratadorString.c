#include "tratadorString.h"

//
char** trataStringPorToken(char* entrada, const char* token){

    char** arr = malloc(5 * sizeof(char*)); 
    for(int i = 0; i < 5; i++) //inicializa array com null
        arr[i] = NULL;
    
    int tam_entrada = strlen(entrada)+1;

    //copia entrada para nova variavel para quebra-la em tokens
    char* cpy_entrada = malloc(sizeof(char) * tam_entrada);
    strcpy(cpy_entrada, entrada);

    char* str = strtok(cpy_entrada, token); //le a primeira string ate o token dado
    for(int i = 0; i < 5; i++){     
        if(!str) break; //para caso nao haja token na string pois leu tudo ou eh uma palavra unica
        
        //aloca e copia a string lida para a string alocada
        int tam_str = strlen(str)+1;
        char* new_str = malloc(sizeof(char) * tam_str);
        
        strcpy(new_str, trim(str)); //remove os espacos antes e dps da string

        arr[i] = new_str; //adiciona a lista de strings

        str = strtok(NULL, "#\n"); //le a proxima string
    }

    free(cpy_entrada);
    return arr;
}


//transforma os comandos lidos do terminal em seus executaveis
void adicionaCaminho(char*** comando){
    char* aux = malloc (50*sizeof(char));
    for(int i = 0; i < 5; i++){
        if(comando[i] != NULL){
            strcpy(aux,comando[i][0]);
            strcpy(comando[i][0], "/bin/");        
            strcat(comando[i][0],aux);
        }
    }
    free(aux);
}


//remove espacos no inicio da string
char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}


//remove espacos no final da string
char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

//remove espacos no inicio e final da string
char *trim(char *s)
{
    return rtrim(ltrim(s)); 
}