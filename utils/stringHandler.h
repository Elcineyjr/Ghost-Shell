#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

int le_entrada(char** input);
char** quebraStringPorToken(char* input, const char* token);
void libera_comandos(char** comandos);
char *ltrim(char*);
char *rtrim(char*);
char *trim(char*);