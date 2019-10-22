#ifndef STRINGHANDLER_H
#define STRINGHANDLER_H

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




int recebe_input(char *input, size_t buffSize);

#endif