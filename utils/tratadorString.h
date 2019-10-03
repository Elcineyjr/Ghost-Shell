#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

void adicionaCaminho(char*** comando);
char** trataStringPorToken(char* entrada, const char* token);

char *ltrim(char*);
char *rtrim(char*);
char *trim(char*);