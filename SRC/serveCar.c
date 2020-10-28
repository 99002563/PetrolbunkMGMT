#include <petrolbunk.h>

void acceptPayment()
{
	sem_post(&finishedcounter);
}

void serveCar(int myCar,int number,int myPump)
{
	printf("Attender %d fills gas in Car %d on pump %d\n",number,myCar,myPump);
	printf("\n\nFilling started\n\n");
	sleep(1);
	printf("filling completed\n");
	printf("Filling finished of Car %d by Attender %d on pump %d\n",myCar,number,myPump);
	sem_post(&finished[myCar]);
	sem_wait(&leave_pump[myPump]);
	printf("Attender %d has seen  Car %d leave pump %d and go to ATM\n",number,myCar,myPump);
	sem_post(&sem_pump);
}