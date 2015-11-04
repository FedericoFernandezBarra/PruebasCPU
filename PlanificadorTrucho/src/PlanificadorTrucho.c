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

int main(void) {
	int socketEscuchaCPU = crearSocket();
	asociarAPuerto(socketEscuchaCPU, PUERTOCPU);
	escucharConexiones(socketEscuchaCPU, 1);
	int socketCPU = crearSocketParaAceptarSolicitudes(socketEscuchaCPU);
	tipoPCB PCB;
	PCB.estado = 'o';
	PCB.ruta = "programa.cod";
	PCB.insPointer = 1;
	PCB.pid = 1;

	int* idCPU;
	recibirMensajeCompleto(socketCPU, &idCPU, sizeof(int));
	printf("CPU RECIBIDA ID: %i\n", idCPU);

	int quantum = 0;
	enviarMensaje(socketCPU, &quantum, sizeof(quantum));
	enviarPCB(socketCPU, &PCB);
	printf("PCB ENVIADO: ");
	imprimirPCB(&PCB);

	char estado = 'B';
	recibirMensajeCompleto(socketCPU, &estado, sizeof(char));
	if(estado == 'B')
	{
		int* tiempoDeEspera;
		recibirMensajeCompleto(socketCPU, &tiempoDeEspera, sizeof(int));
		printf("MENSAJE DE CPU RECIBIDO: %c TIEMPO  DE ESPERA: % i\n", estado, tiempoDeEspera);
	}
	else
	{
		printf("MENSAJE DE CPU RECIBIDO: %c\n", estado);
	}

	tipoPCB* PCBRecibido = recibirPCB(socketCPU);

	printf("PCB DE CPU RECIBIDO: ");
	imprimirPCB(PCBRecibido);

	liberarSocket(socketCPU);
	liberarSocket(socketEscuchaCPU);


	return EXIT_SUCCESS;
}
