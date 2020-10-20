#include <petrolbunk.h>

void acceptPayment();

void CarMaker();


int main() 
{ 
	int iseed=time(NULL);
	srand(iseed);
	int i;
	sem_init(&max_capacity,0,maxCars);
	sem_init(&mutex2,0,1);
	sem_init(&mutex3,0,1);
	sem_init(&mutex4,0,1);
	sem_init(&mutex_queue,0,1);
	sem_init(&sem_queue,0,queueSize);
	sem_init(&sem_pump,0,fuelBays);
	sem_init(&car_ready,0,0);
	sem_init(&finishedcounter,0,0);
	sem_init(&readywithpayment,0,0);

	for(i=0; i<totalCars; i++)
	{ 
		sem_init(&finished[i], 0, 0);
		sem_init(&receipt[i], 0, 0);
	}

	for(i=0; i<fuelBays; i++)
	{
		sem_init(&leave_pump[i],0,0);
        pump[i]=-1;
	}

	if (pipe(pipe1) < 0) 
        printf("can't create pipe1\n"); 
	if (pipe(pipe2) < 0) 
        printf("can't create pipe2\n"); 

	AttenderMaker();
	pthread_create(&atm ,NULL, (void *)&ATM, NULL);
	CarMaker();
}





