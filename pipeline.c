
/**
Este programa en C muestra como se implementa el comando 'ls | wc'

Author: John A. Sanabria
Date: 2020-10-08

Modificado por: Geider Andres Montaño Codigo 201840292
Tiempo: Miercoles 28 de octubre.
*/

// LIBRERIAS UTILIZADAS 
#include <unistd.h> // Manejo de directorios y archivos
#include <stdio.h> // E/s
#include <stdlib.h> // Gestor de memoria dinamica
#include <sys/types.h> // Funciones de busqueda y ordenamiento de directorio
#include <string.h>  // Funciones de cadenas
#include <errno.h> // Muestra los errores en codigo no es obligatoria para la ejecucion del comando pero ayuda a identificar errores

#define READ  0
#define WRITE 1

int main(int argc, char *argv[])  // Edicion del Main para añadir argumentos
{
 
  pid_t pid;
  int fd[2];

  if (pipe(fd) == -1) {
	perror("Creating pipe");
	exit(EXIT_FAILURE);
  }
  		// AQUI SE CREAN LOS PUNTEROS DE LOS DOS COMANDOS REQUIRIDOS EN EL CODIGO

		  // Entrada primer comando
   char *primerComando[10];
   primerComando[0] = strtok(argv[1], " "); // strtok rompe la cadena en segmentos lo que crea una dependencia de caracteres
   for(int i = 1; i < 10; i++)
   {
	   
		primerComando[i] = strtok(NULL, " ");
		if(primerComando[i] == NULL)
		{
			i = 10;
			break;
		}
   }
		// Entrada segundo comando
   char *segundoComando[10];
   segundoComando[0] = strtok(argv[2], " ");
   for(int i = 1; i < 10; i++)
   {
	   
		segundoComando[i] = strtok(NULL, " ");
		if(segundoComando[i] == NULL)
		{
			i = 10;
			break;
		}
   }
// NO TOCAR SWITCH
  switch(pid = fork()) {

  case 0:
 
	// The child process will execute wc.
	// Close the pipe write descriptor.
	close(fd[WRITE]);
	// Redirect STDIN to read from the pipe.
	dup2(fd[READ], STDIN_FILENO);

	// Se cambiaron los argumentos ("wc", "wc", NULL) por los mostrados para que se realice la ejecucion del comando
	execvp(segundoComando[0], segundoComando);

  case -1:
	perror("fork() failed)");
    exit(EXIT_FAILURE);

  default:
	// The parent process will execute ls.
	// Close the pipe read descriptor.
	close(fd[READ]);
	// Redirect STDOUT to write to the pipe.
	dup2(fd[WRITE], STDOUT_FILENO);
	// Ejecuta el primer comando
	execvp(primerComando[0], primerComando);
  }
  
}
/*
 NOTA
 El orden de entrada de comandos no se cambio solo se uso el esquema que ya tenia, se adaptaron y añadieron algunas lineas de codigo
 las cuales estan comentada en español para diferenciarlas mas facil.
 */