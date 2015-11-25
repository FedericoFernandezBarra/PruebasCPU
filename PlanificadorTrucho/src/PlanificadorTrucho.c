/*
 ============================================================================
 Name        : PlanificadorTrucho.c
 Author      : Fede
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <commonsDeAsedio/estructuras.h>

#define PUERTOCPU 4000
#define CANTIDAD_CPUS 4

int main(void) {
	int socketEscuchaCPU = crearSocket();
	asociarAPuerto(socketEscuchaCPU, PUERTOCPU);
	escucharConexiones(socketEscuchaCPU, CANTIDAD_CPUS);


////DATOS QUE ENVIO//////////
	int quantum = 1;

	tipoPCB PCB;
	PCB.estado = 'o';
	PCB.ruta = "programa.cod";
	PCB.insPointer = 1;
	PCB.pid = 1;

////FIN DATOS QUE ENVIO////////

	int socketCPU[CANTIDAD_CPUS + 1];

	socketCPU[0] = crearSocketParaAceptarSolicitudes(socketEscuchaCPU);
	printf("SOCKET MASTER CONECTADO\n");

	int i = 1;
	for(i = 1; i <= CANTIDAD_CPUS; i++)
	{
		socketCPU[i] = crearSocketParaAceptarSolicitudes(socketEscuchaCPU);
		int idCPU;
		recibirMensajeCompleto(socketCPU[i], &idCPU, sizeof(int));
		printf("CPU RECIBIDA ID: %i\n", idCPU);
		enviarMensaje(socketCPU[i], &quantum, sizeof(quantum));
		printf("CPUID: %i QUANTUM ENVIADO: %i\n", idCPU, quantum);
	}

	enviarPCB(socketCPU[1], &PCB);
	printf("PCB ENVIADO: ");
	imprimirPCB(&PCB);


	while(1)
	{
		char estado;
		recibirMensajeCompleto(socketCPU[1], &estado, sizeof(char));

		if(estado == 'B')
		{
			int tiempoDeEspera;
			recibirMensajeCompleto(socketCPU[1], &tiempoDeEspera, sizeof(int));
			printf("MENSAJE DE CPU RECIBIDO: %c TIEMPO  DE ESPERA: % i\n", estado, tiempoDeEspera);
		}
		else
		{
			printf("MENSAJE DE CPU RECIBIDO: %c\n", estado);
		}

		tipoPCB* PCBRecibido = recibirPCB(socketCPU[1]);

		printf("PCB DE CPU RECIBIDO: ");
		imprimirPCB(PCBRecibido);
		enviarPCB(socketCPU[1], PCBRecibido);
		printf("PCB ENVIADO: ");
		imprimirPCB(&PCB);
	}

	liberarSocket(socketCPU);
	liberarSocket(socketEscuchaCPU);


	return EXIT_SUCCESS;
}
