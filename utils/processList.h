#ifndef PROCESS_LIST_H
#define PROCESS_LIST_H

typedef struct processo Process;
typedef struct lista Lista;


Process* cria_processo(int pid, int gid, int eh_ghost);
void libera_processo(Process* processo);
void printa_processo(Process* p);
Lista* cria_lista();
void insere(Lista* lista, Process* processo);
void printa_lista(Lista* lista);
void libera_lista(Lista* lista);





#endif //PROCESS_LIST_H