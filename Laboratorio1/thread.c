/*Nombre: Fernando José Sagastume Cerna
Carnet: 17004989
Sección: A
Ciencias de la Computación VII*/
//------------------------------------------------------------------------------------------------

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int N;

void *myThread(void *vargp) {
	int *myid = (int *)vargp; 
	
	int x=2,y,cont;
	for(cont = 1; cont<=N; x++){
		
			for(y = 2; y<=x; y++){
				if(x%y == 0)
					break;
			}
			if(x==y){
				printf("Thread %d: El número %d es Primo.\n",*myid,x);
				cont++;
				sleep(1);
			}
	}

	return NULL; 
} 

// C Concepts 
// https://gist.github.com/Integralist/6c35d4f26c0c7bf5bdce7b95cfa906b3
int main (int argc , char * argv []) {
	printf("Ingrese Número de Primos: ");
	scanf("%d", &N);
	
	pthread_t tid1,tid2; 
	pthread_create(&tid1, NULL, myThread, (void *)&tid1);
    pthread_create(&tid2, NULL, myThread, (void *)&tid2);

    pthread_exit(NULL);

	return 0;
}