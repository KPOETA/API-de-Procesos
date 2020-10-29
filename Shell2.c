/*
*****************************************************************BY KPOETA***********************************************************
Geider Andres Montaño Zalazar
Univalle
201840292
*/
#include<unistd.h>     
#include<stdio.h>      
#include<sys/wait.h>	
#include<string.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    	int n, i = 1;
		char comando[256];
		char *puntero;

    	if(argc < 2)
    	{
        	printf("Por favor escriba un comando un comando\n");
        	exit(1);
    	}

   	strcpy(comando,argv[i]);
   
   	do
   	{
		if(argv[i] && argv[i+1])
		{
			strcat(argv[1]," "); // comilla
			strcat(argv[1],argv[i+1]); // comilla
			strcat(comando," ");
			puntero = strcat(comando,argv[i+1]);		
			i++;
		}
		else
		{
			puntero = comando;
			break;
		}	
   	}while(1);


	if(n = !fork())
	{
        // Llamadas al sistema

		//execl("bash","bash","-c",argv[1],0);  
		//execl("bash","bash","-c",puntero,0);
		printf("\n");
		exit(1);
	}
	wait(&n); //Esperar a que el proceso hijo termine
	return -1;
}