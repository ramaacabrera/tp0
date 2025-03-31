#ifndef CLIENT_H_
#define CLIENT_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>

#include "utils.h"


t_log* iniciar_logger(void){
    t_log* logger_nuevo = log_create("cliente.log","cliente_logger", true, log_level_from_string("info"));
    if(logger_nuevo == NULL) {
        perror("Algo salio mal al crear el log");
        abort();
    }
	return logger_nuevo;
}
t_config* iniciar_config(void)
{
    t_config* nueva_config = config_create("/home/utnso/tp0/client/cliente.config");
    if(nueva_config == NULL){
        perror("algo salio mal creando la config");
        abort();
    }
    return nueva_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline("> ");

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío

    while(strcmp(leido, "") != 0){
        log_info(logger, ">> %s", leido);
        leido = readline("> ");
    }
	// ¡No te olvides de liberar las lineas antes de regresar!
    free(leido);
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	// Leemos y esta vez agregamos las lineas al paquete
    leido = readline(">>");
    paquete = crear_paquete();
    while(strcmp(leido, "") != 0){
        agregar_a_paquete(paquete, leido, strlen(leido)+1);

        leido = readline(">>");
    }

    enviar_paquete(paquete, conexion);
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	free(leido);
    eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	log_destroy(logger);
    config_destroy(config);
    close(conexion);
}

#endif /* CLIENT_H_ */

