#ifndef SYSWRAPPER_H
#define SYSWRAPPER_H

#include "ghost.h"
#include "stringHandler.h"

void exec(char** comandos);
void execForeground(char** comandos);
void execBackground(char** comandos);

#endif