#ifndef PROCESS_LIST_H
#define PROCESS_LIST_H

typedef struct processo Process;
typedef struct lista Lista;


extern Lista* lista_processos; //lista global usada para controle de processos vivos

Process* cria_processo(int pid, int gid, int eh_ghost);
void libera_processo(Process* processo);
void printa_processo(Process* p);
int eh_ghost(Process* processo);
int get_processo_PID(Process* processo);
int get_processo_GID(Process* processo);
Process* get_lista_prim(Lista* lista);
Lista* cria_lista();
int lista_vazia(Lista* lista);
void insere(Lista* lista, Process* processo);
void printa_lista(Lista* lista);
void libera_lista(Lista* lista);
Process* retira_processo(Lista* lista, int pid);
void mata_todos_do_grupo(Lista* lista, int gid);
void suspende_processos(Lista* lista);
void limpa_lista(Lista* lista);




#endif //PROCESS_LIST_H