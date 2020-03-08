#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void FIFO(void *vargp, int requerimientos[], int requerimientosSize, int cabeza, char direccion[]) {
	printf("%s\n", "-----------------------------------------------");
	printf("%s\n", "First In First Out");
	int avgTime = 0;
	for(int i = 0; i < requerimientosSize; i++){
		avgTime = avgTime + abs(requerimientos[i] - cabeza);
		cabeza = requerimientos[i];
	}
	double promedio = avgTime/requerimientosSize;
	printf("Posicion inicial: %d\n", cabeza);
	printf("%s", "Listado: ");
	for (int j = 0; j < requerimientosSize; j++){
		printf("%d,", requerimientos[j]);
	}
	printf("\nPromedio: %f\n", promedio);

	int suma = 0; 
	for(int y = 0; y < requerimientosSize; y++){
		suma = suma + requerimientos[y];
	}
	int media = suma/requerimientosSize;
	int numerador = 0;
	for(int k = 0; k < requerimientosSize; k++){
		int res = abs(requerimientos[k]-media);
		res = res*res;
		numerador = numerador + res;
	}

	double interior = numerador/requerimientosSize;
	double ds = sqrt(interior);

	printf("Desviacion Estandar: %f\n", ds);

	printf("%s\n", "-----------------------------------------------");
}

void scan_(void *vargp, int requerimientos[], int requerimientosSize, int diskSize, int cabeza, char direccion[]) {
	printf("%s\n","SCAN");

	if(!(strcmp(direccion,"derecha") == 0 || strcmp(direccion,"izquierda") == 0)){
		printf("%s\n", "Direccion indicada invalida, debe ser 'derecha' o 'izquierda'");
		printf("%s\n\n", "Regresando al menu principal...");
		return;
	}

	int menores = 0; 
	for(int i = 0; i < requerimientosSize; i++){
		if(requerimientos[i] < cabeza)
			menores++;
	}

	int parteIzquierda[menores]; //Arreglo para los requerimientos menores al inicio del head
	if(menores > 0){
		int j = 0;
		for (int i = 0; i < requerimientosSize; i++)
		{
	     if(requerimientos[i] < cabeza){
	     	int copia = requerimientos[i];
	     	parteIzquierda[j] = copia;
	     	j++;
	     }
		}
	}
	else {
		return;
	}

	int mayores = requerimientosSize - menores;
	mayores = mayores + 1; 

	int parteDerecha[mayores]; //Arreglo para los requerimientos mayores al inicio del head
	int s = 0;
	for (int i = 0; i < requerimientosSize; i++)
		{
	     if(requerimientos[i] > cabeza){
	     	int copia = requerimientos[i];
	     	parteDerecha[s] = copia;
	     	s++;
	     }
		}

	parteDerecha[mayores-1] = diskSize;

	int aux = 0;
	//Se hace sort del arreglo de los mayores de forma ascendente
		for (int i = 0; i < mayores; i++){
            for (int k = i + 1; k < mayores; k++){

                if (parteDerecha[i] > parteDerecha[k]){
                    aux =  parteDerecha[i];
                    parteDerecha[i] = parteDerecha[k];
                    parteDerecha[k] = aux;
                }

            }
        }


        //Se hace sort del arreglo de los menores de forma descendente
        for (int i = 0; i < menores; i++){
            for (int k = i + 1; k < menores; k++){

                if (parteIzquierda[i] < parteIzquierda[k]){
                    aux = parteIzquierda[i];
                    parteIzquierda[i] = parteIzquierda[k];
                    parteIzquierda[k] = aux;
                }
            }
        }


	if(strcmp(direccion,"derecha") == 0){
		
        printf("%s\n", "-----------------------------------------------");
        printf("Posicion inicial: %d\n", cabeza);

        int avgTime = 0;
        int head = cabeza;
        printf("Listado: ");
        for(int i = 0; i < mayores ; i++){
        	//Calculos para el promedio
        	avgTime = avgTime + abs(parteDerecha[i] - head);
			head = parteDerecha[i];
			//Hace print para el listado
        	if(i==(mayores-1))
        	printf("%d,", parteDerecha[i]);
        	else
        	printf("%d,", parteDerecha[i]);
        }

        for(int i = 0; i < menores; i++){
        	//Calculos para el promedio
        	avgTime = avgTime + abs(parteIzquierda[i] - head);
			head = parteIzquierda[i];
			//Hace print para el listado
        	if(i==(menores-1))
        	printf("%d", parteIzquierda[i]);
        	else
        	printf("%d,", parteIzquierda[i]);
        }

        printf("\n");
        double avg = avgTime/requerimientosSize;
        printf("Promedio: %f\n", avg);

        int suma = 0; 
		for(int y = 0; y < requerimientosSize; y++){
			suma = suma + requerimientos[y];
		}
		//Media aritmetica
		int media = suma/requerimientosSize;
		int numerador = 0;
		for(int k = 0; k < requerimientosSize; k++){
			int res = abs(requerimientos[k]-media);
			res = res*res;
			numerador = numerador + res;
		}

		double interior = numerador/requerimientosSize;
		double ds = sqrt(interior);

		printf("Desviacion Estandar: %f\n", ds);
       
        printf("%s\n", "-----------------------------------------------");
	}

	else {//Empieza direccion izquierda

		//Se agrega el 0 al arreglo de los menores al head
		int newSize = menores + 1; 
		int newParteIzquierda[newSize];
		for(int i = 0; i < newSize; i++){
			if(i!=(newSize-1)){
				newParteIzquierda[i] = parteIzquierda[i];
			}
			else {
				newParteIzquierda[i] = 0;
			}
		}

        printf("%s\n", "-----------------------------------------------");
        printf("Posicion inicial: %d\n", cabeza);

        int avgTime = 0;
        int head = cabeza;
        printf("Listado: ");

        for(int i = 0; i < newSize; i++){
        	//Calculos para el promedio
        	avgTime = avgTime + abs(newParteIzquierda[i] - head);
			head = newParteIzquierda[i];
			//Hace print para el listado
        	if(i==(newSize-1))
        	printf("%d,", newParteIzquierda[i]);
        	else
        	printf("%d,", newParteIzquierda[i]);
        }

        for(int i = 0; i < mayores ; i++){
        	//Calculos para el promedio
        	if(i != (mayores-1)){
        	avgTime = avgTime + abs(parteDerecha[i] - head);
			head = parteDerecha[i];
			//Hace print para el listado
			if(i == (mayores-2))
			printf("%d", parteDerecha[i]);
			else
			printf("%d,", parteDerecha[i]);
			}
        }

        printf("\n");
        double avg = avgTime/requerimientosSize;
        printf("Promedio: %f\n", avg);

        int suma = 0; 
		for(int y = 0; y < requerimientosSize; y++){
			suma = suma + requerimientos[y];
		}
		//Media aritmetica
		int media = suma/requerimientosSize;
		int numerador = 0;
		for(int k = 0; k < requerimientosSize; k++){
			int res = abs(requerimientos[k]-media);
			res = res*res;
			numerador = numerador + res;
		}

		double interior = numerador/requerimientosSize;
		double ds = sqrt(interior);

		printf("Desviacion Estandar: %f\n", ds);
       
        printf("%s\n", "-----------------------------------------------");
	}
}

void c_scan(void *vargp, int requerimientos[], int requerimientosSize, int diskSize, int cabeza, char direccion[]) {
	printf("%s\n","Circular SCAN");

	if(!(strcmp(direccion,"derecha") == 0 || strcmp(direccion,"izquierda") == 0)){
		printf("%s\n", "Direccion indicada invalida, debe ser 'derecha' o 'izquierda'");
		printf("%s\n\n", "Regresando al menu principal...");
		return;
	}

	int menores = 0; 
	for(int i = 0; i < requerimientosSize; i++){
		if(requerimientos[i] < cabeza)
			menores++;
	}

	int mayores = requerimientosSize - menores;
	mayores = mayores + 1; 

	int parteIzquierda[menores]; //Arreglo para los requerimientos menores al inicio del head
	if(menores > 0){
		int j = 0;
		for (int i = 0; i < requerimientosSize; i++){

	     if(requerimientos[i] < cabeza){
	     	int copia = requerimientos[i];
	     	parteIzquierda[j] = copia;
	     	j++;
	     }
		}
	}
	else {
		return;
	}


	int parteDerecha[mayores]; //Arreglo para los requerimientos mayores al inicio del head
	int s = 0;
	for (int i = 0; i < requerimientosSize; i++)
		{
	     if(requerimientos[i] > cabeza){
	     	int copia = requerimientos[i];
	     	parteDerecha[s] = copia;
	     	s++;
	     }
		}

	parteDerecha[mayores-1] = diskSize;

	int aux = 0;
	//Se hace sort del arreglo de los mayores de forma ascendente
		for (int i = 0; i < mayores; i++){
            for (int k = i + 1; k < mayores; k++){

                if (parteDerecha[i] > parteDerecha[k]){
                    aux =  parteDerecha[i];
                    parteDerecha[i] = parteDerecha[k];
                    parteDerecha[k] = aux;
                }

            }
        }


        //Se hace sort del arreglo de los menores de forma descendente
        for (int i = 0; i < menores; i++){
            for (int k = i + 1; k < menores; k++){

                if (parteIzquierda[i] < parteIzquierda[k]){
                    aux = parteIzquierda[i];
                    parteIzquierda[i] = parteIzquierda[k];
                    parteIzquierda[k] = aux;
                }
            }
        }
   
    if(strcmp(direccion,"derecha") == 0){

    	//Se agrega el 0 al arreglo de los menores al head
		int newSize = menores + 1; 
		int newParteIzquierda[newSize];
		newParteIzquierda[0] = 0; 
		for(int i = 1, j = 0; i < newSize; i++,j++){
			newParteIzquierda[i] = parteIzquierda[j];
		}

		int aux1 = 0;
		//Se vuelve a ordenar la lista de los menores de forma ascendente
		for (int i = 0; i < newSize; i++){
            for (int k = i + 1; k < newSize; k++){

                if (newParteIzquierda[i] > newParteIzquierda[k]){
                    aux1 =  newParteIzquierda[i];
                    newParteIzquierda[i] = newParteIzquierda[k];
                    newParteIzquierda[k] = aux1;
                }

            }
        }

        printf("%s\n", "-----------------------------------------------");
        printf("Posicion inicial: %d\n", cabeza);

        int avgTime = 0;
        int head = cabeza;
        printf("Listado: ");
        for(int i = 0; i < mayores ; i++){
        	//Calculos para el promedio
        	avgTime = avgTime + abs(parteDerecha[i] - head);
			head = parteDerecha[i];
			//Hace print para el listado
        	if(i==(mayores-1))
        	printf("%d,", parteDerecha[i]);
        	else
        	printf("%d,", parteDerecha[i]);
        }

        for(int i = 0; i < newSize; i++){
        	//Calculos para el promedio
        	avgTime = avgTime + abs(newParteIzquierda[i] - head);
			head = newParteIzquierda[i];
			//Hace print para el listado
        	if(i==(newSize-1))
        	printf("%d", newParteIzquierda[i]);
        	else
        	printf("%d,", newParteIzquierda[i]);
        }

        printf("\n");
        double avg = avgTime/requerimientosSize;
        printf("Promedio: %f\n", avg);

        int suma = 0; 
		for(int y = 0; y < requerimientosSize; y++){
			suma = suma + requerimientos[y];
		}
		//Media aritmetica
		int media = suma/requerimientosSize;
		int numerador = 0;
		for(int k = 0; k < requerimientosSize; k++){
			int res = abs(requerimientos[k]-media);
			res = res*res;
			numerador = numerador + res;
		}

		double interior = numerador/requerimientosSize;
		double ds = sqrt(interior);

		printf("Desviacion Estandar: %f\n", ds);
       
        printf("%s\n", "-----------------------------------------------");

    }
    else {//Empieza direccion izquierda

    	//Se agrega el 0 al arreglo de los menores al head
		int newSize = menores + 1; 
		int newParteIzquierda[newSize];
		for(int i = 0; i < newSize; i++){
			if(i!=(newSize-1)){
				newParteIzquierda[i] = parteIzquierda[i];
			}
			else {
				newParteIzquierda[i] = 0;
			}
		}

		int aux2 = 0; 
		//Se hace sort del arreglo de los mayores de forma descendente
        for (int i = 0; i < mayores; i++){
            for (int k = i + 1; k < mayores; k++){

                if (parteDerecha[i] < parteDerecha[k]){
                    aux2 = parteDerecha[i];
                    parteDerecha[i] = parteDerecha[k];
                    parteDerecha[k] = aux2;
                }
            }
        }

		printf("%s\n", "-----------------------------------------------");
        printf("Posicion inicial: %d\n", cabeza);

        int avgTime = 0;
        int head = cabeza;
        printf("Listado: ");

        for(int i = 0; i < newSize; i++){
        	//Calculos para el promedio
        	avgTime = avgTime + abs(newParteIzquierda[i] - head);
			head = newParteIzquierda[i];
			//Hace print para el listado
        	if(i==(newSize-1))
        	printf("%d,", newParteIzquierda[i]);
        	else
        	printf("%d,", newParteIzquierda[i]);
        }

        for(int i = 0; i < mayores ; i++){
        	//Calculos para el promedio
        	avgTime = avgTime + abs(parteDerecha[i] - head);
			head = parteDerecha[i];
			//Hace print para el listado
			if(i == (mayores-1))
			printf("%d", parteDerecha[i]);
			else
			printf("%d,", parteDerecha[i]);
			
        }

        printf("\n");
        double avg = avgTime/requerimientosSize;
        printf("Promedio: %f\n", avg);

        int suma = 0; 
		for(int y = 0; y < requerimientosSize; y++){
			suma = suma + requerimientos[y];
		}
		//Media aritmetica
		int media = suma/requerimientosSize;
		int numerador = 0;
		for(int k = 0; k < requerimientosSize; k++){
			int res = abs(requerimientos[k]-media);
			res = res*res;
			numerador = numerador + res;
		}

		double interior = numerador/requerimientosSize;
		double ds = sqrt(interior);

		printf("Desviacion Estandar: %f\n", ds);
       
        printf("%s\n", "-----------------------------------------------");
	}
}

void SSTF(void *vargp, int requerimientos[], int requerimientosSize, int cabeza) {

  int distancias[requerimientosSize];
  for(int i = 0; i < requerimientosSize; i++){
    distancias[i] = abs(cabeza-requerimientos[i]);
  }

  int aux = 0; 
  for(int i = 0; i < requerimientosSize; i++){
      for(int j = i+1; j < requerimientosSize; j++){

        if(distancias[i] > distancias[j]){
            aux = distancias[i];
            distancias[i] = requerimientos[j];
            distancias[j] = aux;

            aux=requerimientos[i];
            requerimientos[i]=requerimientos[j];
            requerimientos[j]=aux;
        }
    }

  }


  printf("%s\n", "-----------------------------------------------");
        printf("Posicion inicial: %d\n", cabeza);

        int avgTime = 0;
        int head = cabeza;
        printf("Listado: ");

        for(int i = 0; i < requerimientosSize; i++){
        	if(i!=(requerimientosSize-1))
        	printf("%d,", requerimientos[i]);
        	else 
        	printf("%d\n", requerimientos[i]);
        }

		  for(int i=1; i < requerimientosSize; i++){
		    avgTime = avgTime+abs(head-requerimientos[i]);
		    head = requerimientos[i];
		  }
        double avg = avgTime/requerimientosSize;
        printf("Promedio: %f\n", avg);

        int suma = 0; 
		for(int y = 0; y < requerimientosSize; y++){
			suma = suma + requerimientos[y];
		}
		//Media aritmetica
		int media = suma/requerimientosSize;
		int numerador = 0;
		for(int k = 0; k < requerimientosSize; k++){
			int res = abs(requerimientos[k]-media);
			res = res*res;
			numerador = numerador + res;
		}

		double interior = numerador/requerimientosSize;
		double ds = sqrt(interior);

		printf("Desviacion Estandar: %f\n", ds);
       
        printf("%s\n", "-----------------------------------------------");
}

int menu(){
	printf("%s\n", "Por favor seleccione una de las siguientes opciones:");
	int tmp;
	printf("\n1 - FIFO\n2 - Scan\n3 - C-Scan\n4 - SSTF\n0 - EXIT\n\nOpción: ");
	scanf("%d", &tmp);
	return tmp;
}

int main ( int argc , char * argv []) {
	printf("%s\n", "Bienvenido al Disk Scheduling °/");
	int op = 5;

	while (op > 0){
		op = menu();
		printf("Procesando opción: %d\n\n", op);
		if ( op >5 || op<=0 ){
			printf("END\n");
			break;
		}
		printf("%s\n", "Por favor ingrese el numero de requerimientos a disco (Numero entero): ");
		int N;
		scanf("%d", &N);

		int requerimientos[N];
		printf("%s\n", "Ingrese los requerimientos por favor: ");
		for(int i = 0; i < N; i++){
  			scanf("%d", &requerimientos[i]);
		}

		printf("%s\n", "Por favor ingrese la el tamaño del disco: ");
		int diskSize;
		scanf("%d", &diskSize);

		printf("%s\n", "Por favor ingrese la posicion inicial de la cabeza lectora: ");
		int cabezaInit;
		scanf("%d", &cabezaInit);

		printf("%s\n", "Por favor ingrese la dirección hacia donde se mueve la cabeza lectora: ");
		char direccion[8];
		scanf("%s", &direccion);
		
		switch(op){
			case 1:
			FIFO(0, requerimientos, N, cabezaInit, direccion);
			break;
			case 2:
			scan_(0, requerimientos, N, diskSize, cabezaInit, direccion);
			break;
			case 3:
			c_scan(0, requerimientos, N, diskSize, cabezaInit, direccion);
			break;
			default:
			case 4:
			SSTF(0, requerimientos, N, cabezaInit);
			break;
		}
	}
}