#include "processList.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <wait.h>


Lista* lista_processos;

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


//verifica se processo é ghost
int eh_ghost(Process* processo){
    return processo->ghost;
}

//retorna pid do processo
int get_processo_PID(Process* processo){
    return processo->pid;
}

//retorna gid do processo
int get_processo_GID(Process* processo){
    return processo->gid;
}

Process* get_lista_prim(Lista* lista){
    if(!lista) return NULL;

    return lista->prim;
}

//cria uma lista vazia de processos
Lista* cria_lista(){
    Lista* lista = malloc(sizeof(Lista));

    lista->prim = NULL;
    lista->ult = NULL;

    return lista;
}


//verifica se lista esta vazia
int lista_vazia(Lista* lista){
    if(!lista) return 1;

    if(!lista->prim) return 1;

    return 0;
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

void limpa_lista(Lista* lista){
    int pid;
    Process* p = lista -> prim;
    while(p){
        pid = p->pid;
        Process* aux = p->prox; //guarda o prox, para n perder a referencia caso for liberar o processo atual

        if(kill(pid,0)){ // caso processo não exista mais
            retira_processo(lista,pid);
            libera_processo(p);
        }
        p = aux;
    }
}

//retira processo da lista
Process* retira_processo(Lista* lista, int pid){
    if(!lista) return NULL;

    //lista vazia
    if(!lista->prim) return NULL;


    Process* aux = lista->prim;
    //se contem apenas um processo
    if(lista->prim == lista->ult){
        lista->prim = NULL;
        lista->ult = NULL;
        return aux;
    }

    Process* ant = NULL;
    while(aux){
        //caso encontrou um processo com o pid especificado
        if(aux->pid == pid){

            //caso o anterior nao seja nulo, entao o processo nao é o primeiro da lista
            if(ant){
                ant->prox = aux->prox; //faz o anterior apontar pro prox do processo a ser removido
            }else{
                lista->prim = aux->prox; //atualiza o primeiro da lista
            }
            
            //limpa prox do processo a ser removido 
            aux->prox = NULL; 

            return aux;
        }

        //atualiza ponteiros avançando na lista 
        ant = aux;
        aux = aux->prox; 
    }

    return NULL; //nao achou nenhum processo com o pid dado

}


//mata todos os processos do grupo especificado (incluindo ghosts) 
void mata_todos_do_grupo(Lista* lista, int gid){
    if(!lista) return;

    Process* aux = lista->prim;
    while(aux){
        //remove todos os processos com o mesmo gid da lista de processos vivos
        if(aux->gid == gid){
            //guarda o pid do processo a ser removido e faz aux apontar pro prox da lista pois quando retirado da lista sera perdida a referencia
            int pid_ = aux->pid;
            aux = aux->prox;

            //retira da lista de processos vivos
            Process* removido = retira_processo(lista, pid_);

            //checa se a retira_processo retornou algum processo e entao libera tal processo
            if(removido) libera_processo(removido);

            continue;
        }

        aux = aux->prox;
    }

    killpg(gid, SIGKILL);
}




//suspende todos os processos filhos (diretos e indiretos) da shell
void suspende_processos(Lista* lista){
    if(!lista) return;

    Process* aux = lista->prim;
    while(aux){
        killpg(aux->gid, SIGTSTP); //Envia o sinal de suspençao para todos processos daquele grupo

        aux = aux->prox;
    }
}