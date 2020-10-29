
/**
Este programa en C muestra como se implementa el comando 'ls | wc'

Author: John A. Sanabria
Date: 2020-10-08

Modificado por: Geider Andres Montaño Codigo 201840292
Tiempo: Miercoles 28 de octubre.
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#define READ  0
#define WRITE 1

int main(int argc, char *argv[]) {
 
  pid_t pid;
  int fd[2];

  if (pipe(fd) == -1) {
	perror("Creating pipe");
	exit(EXIT_FAILURE);
  }
   char *primerComando[10];
   primerComando[0] = strtok(argv[1], " ");
   //printf("%s\n",primerComando[0]);
   for(int i = 1; i < 10; i++)
   {
	   
		primerComando[i] = strtok(NULL, " ");
		if(primerComando[i] == NULL)
		{
			i = 10;
			break;
		}
		//printf("%s\n",primerComando[i]);
   }
   char *segundoComando[10];
   segundoComando[0] = strtok(argv[2], " ");
   //printf("%s\n",segundoComando[0]);
   for(int i = 1; i < 10; i++)
   {
	   
		segundoComando[i] = strtok(NULL, " ");
		if(segundoComando[i] == NULL)
		{
			i = 10;
			break;
		}
   }

  switch(pid = fork()) {

  case 0:
 
	// The child process will execute wc.
	// Close the pipe write descriptor.
	close(fd[WRITE]);
	// Redirect STDIN to read from the pipe.
	dup2(fd[READ], STDIN_FILENO);
	// Execute second command

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
	// Execute first command
	execvp(primerComando[0], primerComando);
  }
  
}