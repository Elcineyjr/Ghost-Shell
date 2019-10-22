//File: Aircraft.h
#ifndef GHOST_H
#define GHOST_H

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <errno.h>

#include "listas.h"

int fork_gs();
int gerarGhost();

#endif
