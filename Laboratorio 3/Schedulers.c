#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


void arraycp(char * source[], char * dest[], int n){
	for(int i = 0 ; i < n ; i++){
		dest[i] = source[i];
	}
}

void arrayCpInt(int source[], int dest[], int n){
	for(int i = 0 ; i < n ; i++){
		dest[i] = source[i];
	}
}

void output(void *vargp) {
	printf("|-------|-------|-------|-------|-------|-------|-------|-------|-------| \n");
	printf("|PXX\t|QU\t|QM\t|AT\t|BT\t|ET\t|WT\t|RT\t|TT\t|\n");
	printf("|-------|-------|-------|-------|-------|-------|-------|-------|-------| \n\n");
} 

void FCFS(void *vargp, char *procesosOr[], int ATor[], int BTor[], int N) {
	printf(" --> FCFS\n");
	printf("|-------|-------|-------|-------|-------|-------|-------| \n");
	printf("|PXX\t|AT\t|BT\t|ET\t|WT\t|RT\t|TT\t|\n");
	
	char *procesos[N];
	int AT[N];
	int BT[N];

	arraycp(procesosOr, procesos, N);
	arrayCpInt(ATor, AT, N);
	arrayCpInt(BTor, BT, N);

	int k, h;
    int temp,temp1;
    char *temp2;
    for (k = 0; k < N - 1; k++)
    {
        for (h = k + 1; h < N; h++)
        {
            //Se hace sort a los procesos respecto su arrival time
            if (AT[k] > AT[h])
            {
                temp = AT[k];
                temp1 = BT[k];
                temp2 = procesos[k];
                AT[k] = AT[h];
                AT[h] = temp;
                BT[k] = BT[h];
                BT[h] = temp1;
                procesos[k] = procesos[h];
                procesos[h] = temp2;
            }
        }
	}

	int ET = BT[0];
	int waitTime,responseTime,TT;
	int E_T[N],WT[N],RT[N],TuT[N];
    for(int i = 0; i < N; i++){
		if(i != 0)
		ET = ET+BT[i];

		waitTime = ET-(BT[i]+AT[i]);
		responseTime = waitTime;
		TT = ET-AT[i];
		E_T[i]=ET;
		WT[i]=waitTime;
		RT[i]=responseTime;
		TuT[i]=TT;
		printf("|-------|-------|-------|-------|-------|-------|-------| \n");
		printf("|%s\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|\n",procesos[i],AT[i],BT[i],ET,waitTime,responseTime,TT);
		//printf("|-------|-------|-------|-------|-------|-------|-------| \n");
	}

	double ATavg=0.0;
	double BTavg=0.0;
	double ETavg=0.0;
	double WTavg=0.0;
	double RTavg=0.0;
	double TTavg=0.0;

	for(int i = 0; i < N; i++){
		ATavg = (double)AT[i]+ATavg;
		BTavg = (double)BT[i]+BTavg;
		ETavg = (double)E_T[i]+ETavg;
		WTavg = (double)WT[i]+WTavg;
		RTavg = (double)RT[i]+RTavg;
		TTavg = (double)TuT[i]+TTavg;
	}

	ATavg = ATavg/N;
	BTavg = BTavg/N;
	ETavg = ETavg/N;
	WTavg = WTavg/N;
	RTavg = RTavg/N;
	TTavg = TTavg/N;
	printf("|-------|-------|-------|-------|-------|-------|-------| \n");
	printf("|TH\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|\n",(int)ATavg,(int)BTavg,(int)ETavg,(int)WTavg,
			(int)RTavg,(int)TTavg);
	printf("|-------|-------|-------|-------|-------|-------|-------|\n\n");
} 

void PS(void *vargp, char *procesosOr[], int ATor[], int BTor[], int Vor[] ,int N) {
	printf(" --> PS\n");
	printf("|-------|-------|-------|-------|-------|-------|-------|-------| \n");
	printf("|PXX\t|PR\t|AT\t|BT\t|ET\t|WT\t|RT\t|TT\t|\n");

	char *procesos[N];
	int AT[N];
	int BT[N];
	int V[N];

	arraycp(procesosOr, procesos, N);
	arrayCpInt(ATor, AT, N);
	arrayCpInt(BTor, BT, N);
	arrayCpInt(Vor, V, N);

	int k, h, f,s;
    int temp,temp1,temp3,temp4,temp5,temp6;
    char *temp2;
    char *temp7;
    for (k = 0; k < N - 1; k++)
    {
        for (h = k + 1; h < N; h++)
        {
            //Se hace sort a los procesos respecto su arrival time
            if (AT[k] > AT[h])
            {
                temp = AT[k];
                temp1 = BT[k];
                temp2 = procesos[k];
                temp3 = V[k];
                AT[k] = AT[h];
                AT[h] = temp;
                BT[k] = BT[h];
                BT[h] = temp1;
                procesos[k] = procesos[h];
                procesos[h] = temp2;
                V[k] = V[h];
                V[h] = temp3;
            }
        }
	}

	for (f = 0; f < N - 1; f++)
    {
        for (s = f + 1; s < N; s++)
        {
            //Se hace sort a los procesos respecto su prioridad
            if ((AT[f] == AT[s]) && (V[f] < V[s]))
            {
                temp4 = AT[f];
                temp5 = BT[f];
                temp7 = procesos[f];
                temp6 = V[f];
                AT[f] = AT[s];
                AT[s] = temp4;
                BT[f] = BT[s];
                BT[s] = temp5;
                procesos[f] = procesos[s];
                procesos[s] = temp7;
                V[f] = V[s];
                V[s] = temp6;
            }
        }
	}

	int ET = BT[0];
	int waitTime,responseTime,TT;
	int E_T[N],WT[N],RT[N],TuT[N];
    for(int i = 0; i < N; i++){
		if(i != 0)
		ET = ET+BT[i];

		waitTime = ET-(BT[i]+AT[i]);
		responseTime = waitTime;
		TT = ET-AT[i];
		E_T[i]=ET;
		WT[i]=waitTime;
		RT[i]=responseTime;
		TuT[i]=TT;
		printf("|-------|-------|-------|-------|-------|-------|-------|-------| \n");
		printf("|%s\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|\n",procesos[i],V[i],AT[i],BT[i],ET,waitTime,
			responseTime,TT);
	}

	double ATavg=0.0;
	double BTavg=0.0;
	double ETavg=0.0;
	double WTavg=0.0;
	double RTavg=0.0;
	double TTavg=0.0;
	double PRavg=0.0;

	for(int i = 0; i < N; i++){
		ATavg = (double)AT[i]+ATavg;
		BTavg = (double)BT[i]+BTavg;
		ETavg = (double)E_T[i]+ETavg;
		WTavg = (double)WT[i]+WTavg;
		RTavg = (double)RT[i]+RTavg;
		TTavg = (double)TuT[i]+TTavg;
		PRavg = (double)V[i]+PRavg;
	}

	ATavg = ATavg/N;
	BTavg = BTavg/N;
	ETavg = ETavg/N;
	WTavg = WTavg/N;
	RTavg = RTavg/N;
	TTavg = TTavg/N;
	PRavg = PRavg/N;
	printf("|-------|-------|-------|-------|-------|-------|-------|-------| \n");
	printf("|TH\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|\n",(int)PRavg,(int)ATavg,(int)BTavg,(int)ETavg,(int)WTavg,
			(int)RTavg,(int)TTavg);
	printf("|-------|-------|-------|-------|-------|-------|-------|-------|\n\n");

} 

void RR(void *vargp, char *procesosOr[], int ATor[], int BTor[], int N) {
	printf(" --> RR\n");
	printf("|-------|-------|-------|-------|-------|-------|-------| \n");
	printf("|PXX\t|AT\t|BT\t|ET\t|WT\t|RT\t|TT\t|\n");

	char *procesos[N];
	int AT[N];
	int BT[N];

	arraycp(procesosOr, procesos, N);
	arrayCpInt(ATor, AT, N);
	arrayCpInt(BTor, BT, N);
	int QM = 2;

	int k, h;
    int temp,temp1;
    char *temp2;
    for (k = 0; k < N - 1; k++)
    {
        for (h = k + 1; h < N; h++)
        {
            //Se hace sort a los procesos respecto su arrival time
            if (AT[k] > AT[h])
            {
                temp = AT[k];
                temp1 = BT[k];
                temp2 = procesos[k];
                AT[k] = AT[h];
                AT[h] = temp;
                BT[k] = BT[h];
                BT[h] = temp1;
                procesos[k] = procesos[h];
                procesos[h] = temp2;
            }
        }
	}

	int ET[N],RT[N],TT[N], WT[N];
	for(int i = 0; i < N; i++){
		RT[i] = BT[i];
	}

	int aux = 0;
	int execT = 0;
	int rp = N;
	
	for(int i = 0 ; rp != 0 ;){
        
        if(RT[i] <= QM && RT[i] > 0){
            execT += RT[i];
            RT[i] = 0;
            aux=1;
        }

        else if(RT[i] > 0){
            RT[i] = RT[i] - QM;
            execT += QM;
        }

        if(aux == 1 && RT[i] == 0){
            WT[i] = execT - AT[i] - BT[i];
            TT[i] = execT - AT[i];
            aux = 0;
            rp--;
        }

        if(i == N-1){
            i = 0;
        }
        else if(AT[i+1] <= execT){
            i++;
        }
        else
            i=0;
}
	
	for(int m = 0; m < N; m++){
		ET[m] = TT[m] + AT[m];
	}

   for(int i = 0; i < N; i++){

		printf("|-------|-------|-------|-------|-------|-------|-------| \n");
		printf("|%s\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|\n",procesosOr[i],AT[i],BTor[i],ET[i],WT[i],
			RT[i],TT[i]);
	}

	double ATavg=0.0;
	double BTavg=0.0;
	double ETavg=0.0;
	double WTavg=0.0;
	double RTavg=0.0;
	double TTavg=0.0;
	double PRavg=0.0;

	for(int i = 0; i < N; i++){
		ATavg = (double)AT[i]+ATavg;
		BTavg = (double)BT[i]+BTavg;
		ETavg = (double)ET[i]+ETavg;
		WTavg = (double)WT[i]+WTavg;
		RTavg = (double)RT[i]+RTavg;
		TTavg = (double)TT[i]+TTavg;
	}

	ATavg = ATavg/N;
	BTavg = BTavg/N;
	ETavg = ETavg/N;
	WTavg = WTavg/N;
	RTavg = RTavg/N;
	TTavg = TTavg/N;

	printf("|-------|-------|-------|-------|-------|-------|-------| \n");
	printf("|TH\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|\n",(int)ATavg,(int)BTavg,(int)ETavg,(int)WTavg,
			(int)RTavg,(int)TTavg);
	printf("|-------|-------|-------|-------|-------|-------|-------|\n");

	printf("Quatum Time = %d\n\n", QM);
} 

void MLFQS(void *vargp) {
	printf(" --> MLFQS\n");
	output(0);
} 

int menu(){
	int tmp;
	printf("############\n1 - FCFS\n2 - PS\n3 - RR\n4 - MLFQS\n0 - EXIT\n\nSeleccione Opción: ");
	scanf("%d", &tmp);
	return tmp;
}


int main ( int argc , char * argv []) {
	int op = 9;
	pid_t pid;

/*------------------------------------------------------------------------------------------------------*/

	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("listProcess.cpu", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    
    char **lineFiles;
    lineFiles = malloc(40 * sizeof(char*));

    int pos = 0; 
    while ((read = getline(&line, &len, fp)) != -1) {

        	lineFiles[pos] = malloc(strlen(line) + 1);
        	strcpy(lineFiles[pos], line);
        	pos++;
        	
        }
    
    fclose(fp);
    if (line)
        free(line);

    int cont = 0;
	char **tokLines;
	tokLines = malloc(140 * sizeof(char*));
    for(int i = 1; i < 40; i++){
    	
	    char *p = strtok (lineFiles[i], "\t");
	   
	    while (p != NULL)
	    {
	    	tokLines[cont] = malloc(strlen(p) + 1);
	        strcpy(tokLines[cont], p);
	        cont++;
	        p = strtok (NULL, "\t");
	        
	    }
    }

   	int tokSize = 0; 
   	while(tokLines[tokSize]!=NULL){
   		tokSize+=1;
   	}

   	/*---------------------------------------------------------------------------------------------------*/
   	/* En esta sección se definen los procesos, los Arrival Times, los Burst Times y V */

   	int processLen = 0;
   	for(int pr = 0; pr < tokSize; ){
   		pr+=4;
   		processLen++;
   	}

   	char *procesos[processLen]; //Procesos
   	int posi = 0;
   	for(int pr = 0; pr < tokSize; ){
   		procesos[posi] = tokLines[pr];
   		pr+=4;
   		posi++;
   	}

   	int AT[processLen]; //Arrival Time
   	int posi1 = 0;
   	for(int pr = 1; pr < tokSize; ){
   		AT[posi1] = atoi(tokLines[pr]);
   		pr+=4;
   		posi1++;
   	}

   	int BT[processLen]; //Burst Time
   	int posi2 = 0;
   	for(int pr = 2; pr < tokSize; ){
   		BT[posi2] = atoi(tokLines[pr]);
   		pr+=4;
   		posi2++;
   	}

   	int V[processLen]; //V
   	int posi3 = 0;
   	for(int pr = 3; pr < tokSize; ){
   		V[posi3] = atoi(tokLines[pr]);
   		pr+=4;
   		posi3++;
   	}

/*-------------------------------------------------------------------------------------------------------*/
	while (op > 0){
		op = menu();
		printf("Procesando opción: %d\n", op);
		if ( op >5 || op<=0 ){
			printf("### END ###\n");
			break;
		}
		printf("### BEGIN ###\n");
		switch(op){
			case 1:
			FCFS(0,procesos,AT,BT,processLen);
			break;
			case 2:
			PS(0,procesos,AT,BT,V,processLen);;
			break;
			case 3:
			RR(0,procesos,AT,BT,processLen);
			break;
			default:
			case 4:
			MLFQS(0);
			break;
		}
	}
	if(lineFiles)
		free(lineFiles);
	if(tokLines)
		free(tokLines);
	return 0;
}