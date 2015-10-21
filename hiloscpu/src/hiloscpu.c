#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <commons/string.h>
#define CANTIDAD_CPUS 4

typedef struct{
	int idCPU;
	char* texto;
}t_hiloCPU;


void* unCPU(t_hiloCPU* CPU);

int main(void) {

	t_hiloCPU* CPU;
	int i = 0;
	pthread_t* hiloCPU[CANTIDAD_CPUS];
	CPU->texto = "HOLA";
	int errorDeHilo;

	while(i < CANTIDAD_CPUS)
	{
		CPU->idCPU = i;
		errorDeHilo = pthread_create(&hiloCPU[i], NULL, unCPU, CPU);
		printf("HILO %i CREADO", CPU->idCPU);
		pthread_join(hiloCPU[i], NULL); //Se pudre todo si saco esto
		i++;
	}
	return 0;
}

void* unCPU(t_hiloCPU* CPU)
{
	printf("\nHILO %i FINALIZADO\n", CPU->idCPU);
	printf("TEXTO: %s\n\n", CPU->texto);
	return 0;
}
