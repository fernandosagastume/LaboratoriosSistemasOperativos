/*Nombre: Fernando José Sagastume Cerna
Carnet: 17004989
Sección: A
Ciencias de la Computación VII*/
//------------------------------------------------------------------------------------------------
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main ( int argc , char * argv []) {
	int N;
	int pid;
	int x=2,y,cont,cont1,x1=2,y1;
	
	printf("Ingrese Número de Primos: ");
	scanf("%d", &N);

  pid=fork();
 
	if( pid > 0){
			// Returned to parent or caller. The value contains process ID of newly created child process.
			for(cont = 1; cont<=N; x++){
		
			for(y = 2; y<=x; y++){
				if(x%y == 0)
					break;
			}
			if(x==y){
				printf("Process %d: El número %d es Primo.\n",getpid (),x);
				cont++;
			}
	}
		} else {
			// Returned to the newly created child process
			printf("\n");
			for(cont1 = 1; cont1<=N; x1++){
		
			for(y1 = 2; y1<=x1; y1++){
				if(x1%y1 == 0)
					break;
			}
			if(x1==y1){
				printf("Process %d: El número %d es Primo.\n",getpid(),x1);
				cont1++;
				sleep(1);
			}
	}
		}
	return 0;
}