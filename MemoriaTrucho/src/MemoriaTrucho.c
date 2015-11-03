/*
 ============================================================================
 Name        : MemoriaTrucho.c
 Author      : Fede
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <commonsDeAsedio/estructuras.h>

#define PUERTOCPU 5000

int main(void) {
	int socketEscuchaCPU = crearSocket();
	asociarAPuerto(socketEscuchaCPU, PUERTOCPU);
	escucharConexiones(socketEscuchaCPU, 1);
	int socketCPU = crearSocketParaAceptarSolicitudes(socketEscuchaCPU);

	tipoInstruccion* instruccion = recibirInstruccion(socketCPU);


	return EXIT_SUCCESS;
}
