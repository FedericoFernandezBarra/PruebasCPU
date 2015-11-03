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

	int* idCPU;
	recibirMensajeCompleto(socketCPU, &idCPU, sizeof(int));
	printf("CPU RECIBIDA ID: %i\n", idCPU);

	int quantum = 3;
	enviarMensaje(socketCPU, &quantum, sizeof(quantum));


	tipoPCB* PCB;
	PCB->estado = 'o';
	PCB->ruta = "programa.cod";
	PCB->insPointer = 1;
	PCB->pid = 1;
	enviarPCB(socketCPU, PCB);

	return EXIT_SUCCESS;
}
