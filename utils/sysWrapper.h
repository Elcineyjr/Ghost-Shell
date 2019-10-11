#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

void exec(char** comandos);
void execForeground(char** comandos);
void execBackground(char** comandos);