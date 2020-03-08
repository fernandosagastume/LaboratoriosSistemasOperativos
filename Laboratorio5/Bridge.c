#include  <stdio.h>
#include  <stdlib.h>
#include  <stdbool.h>
#include  <time.h>
#include <pthread.h>
#include <unistd.h>

//pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;
//pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
//pthread_cond_t  condition_cond  = PTHREAD_COND_INITIALIZER;

/*------------------------------------------------------------------------
						VARIABLES GLOBALES
-------------------------------------------------------------------------*/
static int N; //personas que cruzan el puente
static int max_crossing_inges = 4; //Numero maximo de personas en el puente

static int cont_inges = 0; //Cantidad actual de ingenieros en el puente
static int direccion_actual = 0; //direccion actual en la cual los inges van en el puente

static pthread_mutex_t mutexLock;
pthread_mutex_t terminal;

struct WaitingQueue {
	int derecha; //Cantidad de inges esperando por el lado derecho
	int izquierda; //Cantidad de inges esperando por el lado izquierdo
	//PARA MAÑANA BUSCAR UNA FORMA DE METER LOS INGES AQUI 
};

//Se inicializa la waiting queue en 0 para ambas direcciones
static struct WaitingQueue waitingQueue = {0,0};

struct CondVars{
	pthread_cond_t condDerecha;
	pthread_cond_t condIzquierda;
};

//Se incializan las condvars de las direcciones
static struct CondVars condvars = {PTHREAD_COND_INITIALIZER,PTHREAD_COND_INITIALIZER};
//--------------------------------------------------------------------------

bool cantCross(){return false;}
bool canCross(int direccion){
	if(cont_inges == 0)
		return true;
	else if ((direccion == direccion_actual)&&(cont_inges < max_crossing_inges))
		return true;
	else 
		cantCross();
}

pthread_cond_t whichCond(int direccion){
	pthread_cond_t condi;
	(direccion == 0)?(condi = condvars.condDerecha):(condi = condvars.condIzquierda);
	return condi;
}

void  accessBridge(int direccion){
	if(!((direccion == 0)||(direccion == 1))){
		printf("%s\n", "Direccion invalida, debe ser derecha -> 0, izquierda -> 1");
		return;
	}
	pthread_mutex_lock(&mutexLock);
	//Si un inge no puede pasar, tiene que esperar
	if(!canCross(direccion)){
		//Como no puede cruzar el puente, se agrega a la cola de espera un inge
		(direccion == 0)?(waitingQueue.derecha++):(waitingQueue.izquierda++);
		pthread_cond_t condvarDir = whichCond(direccion);
		while(!canCross(direccion)){
			pthread_cond_wait(&condvarDir, &mutexLock); 
		}
		(direccion == 0)?(waitingQueue.derecha--):(waitingQueue.izquierda--);
	}
	//Como ya se cumple la funcion canCross() entonces se puede accesar el bridge
	direccion_actual = direccion;
	cont_inges++;
	pthread_mutex_unlock(&mutexLock);
}

void signalOpositeWaiter(int direccion){
	int d_op = 1 - direccion;
	int opositeWaiters;
	(d_op == 0)?(opositeWaiters = waitingQueue.derecha):(opositeWaiters = waitingQueue.izquierda);
	int currentWaiters;
	(direccion == 0)?(currentWaiters = waitingQueue.derecha):(currentWaiters = waitingQueue.izquierda);
	pthread_cond_t condvarOp = whichCond(opositeWaiters);
	pthread_cond_t condvarCurr = whichCond(direccion);
	(opositeWaiters != 0)?(pthread_cond_signal(&condvarOp)):(pthread_cond_signal(&condvarCurr));
}

void  exitBridge(int direccion){
	if(!((direccion == 0)||(direccion == 1))){
		printf("%s\n", "Direccion invalida, debe ser derecha -> 0, izquierda -> 1");
		return;
	}
	pthread_mutex_lock(&mutexLock);
	//Un inge llega a una de las puntas del puente
	cont_inges--;
	//Se verifica si aun hay inges en el puente 
	if(cont_inges > 0){
		pthread_cond_t condvarDir = whichCond(direccion);
		pthread_cond_signal(&condvarDir);
	}
	else{
		signalOpositeWaiter(direccion);
	}
	pthread_mutex_unlock(&mutexLock);
}

void* inge(void *args){
	int time = (rand()%(3 - 0 + 1)) + 0;
	sleep(time);
	pthread_mutex_lock(&terminal);
	printf("Numero random -> %d\n", time); 
	pthread_mutex_unlock(&terminal);

	pthread_exit(NULL);
}

struct IngesInformation{
	int *ingesD; //Direccion para cada n inge.
	char *ing; //lista de inges
};

int main() {
	printf("%s\n", "///Bienvenido a la Simulación///");
	printf("%s", "¿Cuantas personas cruzaran el puente? ");
	scanf("%d", &N);

	srand(time(NULL));
	int ingesDir[N];
	//Se crean direcciones random para cada inge
	for(int i = 0; i < N; i++){
		int num = (rand() % 
           (1 + 1)); 
  		ingesDir[i] = num;
	}

  	for(int i = 0; i < N; i++){
  		if(ingesDir[i] == 0)
  			printf("Inge %d camina hacia la derecha\n", i+1);
  		else
  			printf("Inge %d camina hacia la izquierda\n", i+1);
  	}

  	struct IngesInformation info;
    info.ingesD = malloc(N * sizeof(int *));
    info.ingesD = ingesDir;

    for (int i = 0; i < N; ++i)
    {
    	printf("Direccion -> %d\n", info.ingesD[i]);
    }

  	pthread_mutex_init(&mutexLock, NULL);
  	pthread_mutex_init(&terminal, NULL);

	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, &inge, NULL); 
	pthread_create(&thread2, NULL, &inge, NULL);
    pthread_exit(NULL); 
	//accessBridge(1);

	//pthread_create( &thread1, NULL, &functionCount1, NULL);
	//pthread_create( &thread2, NULL, &functionCount2, NULL);
	//pthread_join( thread1, NULL);
	//pthread_join( thread2, NULL);

	exit(0);
}
