#include "processList.h"

#include <stdio.h>
#include <stdlib.h>

struct processo{
    int pid; //process id
    int gid; //group id
    int ghost; //boolean
    Process* prox;
};


struct lista{
    Process* prim;
    Process* ult;
};


//cria um processo
Process* cria_processo(int pid, int gid, int eh_ghost){
    Process* p = malloc(sizeof(Process));

    p->pid = pid;
    p->gid = gid;
    p->ghost = eh_ghost;
    p->prox = NULL;

    return p;
}


//libera um unico processo
void libera_processo(Process* processo){
    if(!processo) return;
    
    free(processo);
}


//printa processo
void printa_processo(Process* p){
    printf("PID: %d\nGID: %d\nGhost: %d\n", p->pid, p->gid, p->ghost);
}


//cria uma lista vazia de processos
Lista* cria_lista(){
    Lista* lista = malloc(sizeof(Lista));

    lista->prim = NULL;
    lista->ult = NULL;

    return lista;
}


//insere um processo numa lista de processos
void insere(Lista* lista, Process* processo){
    //caso a lista seja nula
    if(!lista){
        lista = cria_lista();
    }

    //caso a lista esteja vazia
    if(!lista->prim){
        lista->prim = processo;
        lista->ult = processo;
        return;
    }

    //adiciona o processo no final da lista
    lista->ult->prox = processo;
    lista->ult = processo;
}


//printa lista de processos
void printa_lista(Lista* lista){
    if(!lista){
        printf("Lista nula.\n");
        return;
    } 

    Process* aux = lista->prim;
    while(aux){
        printa_processo(aux);
        aux = aux->prox;
    }
}


//libera lista de processos
void libera_lista(Lista* lista){
    if(!lista) return;

    Process* aux = lista->prim;
    while(aux){
        lista->prim = aux->prox;
        libera_processo(aux);
        aux = lista->prim;
    }
    free(lista);
}