#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>


#include "utils/stringHandler.h"
#include "utils/sysWrapper.h"
#include "utils/signalHandler.h"
#include "utils/processList.h"



int main(int argc, char* argv[]){
    
    printf("criando lista\n");
    Lista* l = cria_lista();

    printf("criando processsos\n");
    Process* p1 = cria_processo(10,100,0);
    Process* p2 = cria_processo(20,100,0);
    Process* p3 = cria_processo(30,100,0);
    Process* p4 = cria_processo(40,100,1);

    printf("inserindo na lista\n");
    insere(l, p1);
    insere(l, p2);
    insere(l, p3);
    insere(l, p4);

    printf("printa lista\n");
    printa_lista(l);

    printf("liberando lista\n");
    libera_lista(l);

    return 0;
}


