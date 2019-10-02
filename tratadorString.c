#include "tratadorString.h"

void adicionaCaminho(char** comando){
    char* aux = malloc (50*sizeof(char));
    for(int i = 0; i < 5; i++){
        if(comando[i] != NULL){
        strcpy(aux,comando[i]);
        strcpy(comando[i], "/bin/");        
        strcat(comando[i],aux);
        }
    }
    free(aux);
}

char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s)); 
}