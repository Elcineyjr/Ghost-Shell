#ifndef SYS_WRAPPER_H
#define SYS_WRAPPER_H

#define CMD_NOT_FOUND_ERROR 10

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include "stringHandler.h"
#include "processList.h"
#include "signalHandler.h"

int gerarGhost();
void exec(char** comandos);
void execForeground(char** comandos);
void execBackground(char** comandos);


#endif