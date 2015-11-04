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
	int i = 0;
	while(i<4)
	{
		tipoInstruccion* instruccion = recibirInstruccion(socketCPU);
		printf("INSTRUCCION RECIBIDA | pID: %i | instruccion: %c | numeroDePagina: %i | texto: %s\n", instruccion->pid, instruccion->instruccion, instruccion->nroPagina, instruccion->texto);

		tipoRespuesta respuesta;
		respuesta.respuesta = 'D';
		respuesta.informacion = "contenido de la pagina";
		enviarRespuesta(socketCPU, &respuesta);
		printf("RESPUESTA ENVIADA | respuesta: %c | informacion: %s\n", respuesta.respuesta, respuesta.informacion);
		i++;
	}
	liberarSocket(socketCPU);
	liberarSocket(socketEscuchaCPU);
	return EXIT_SUCCESS;
}
