#include "ghost.h"
int fork_gs(){
	int f, f1;
	f = fork(); // gera o processo filho normal, que fará a execução do comando no sysWrapper.c
	if(gerarGhost()){ // Número aleatório, 50% de chance de entrar no if		
		if (f == 0){ // Para o processo filho gerado em cima:			
			f1 = fork(); // gera ghost filho
			if (f1==0){
				return f1; // se for o filho, retorna o pid para a função de execucao no sysWrapper.c.
			}
		}
	}
	return f;
}

int gerarGhost(){
	srand((unsigned) time(NULL));
	return (rand() % 2);
}

