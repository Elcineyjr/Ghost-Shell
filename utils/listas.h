#ifndef LISTAS_H
#define LISTAS_H

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h> 

#define maxFilhos 99

__pid_t *filhos;

void inicializa_filhos();
void addFilho(__pid_t pid);
int tem_filho();//pergunta se a shell tem filhos
void para_filhos_e_Ghosts();//ctrl+z em todos os processos, ate ghosts
void cleanEdie();
void mywait();

#endif