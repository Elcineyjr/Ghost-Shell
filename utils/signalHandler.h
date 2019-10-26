#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANDLER_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include "listas.h"

void trata_SIGINT(int i);
void suspende_filhos(int i);

#endif