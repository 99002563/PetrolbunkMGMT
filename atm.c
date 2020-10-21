#include <petrolbunk.h>

void ATM() 
{
	int Car;
	int MyId = -1;
	int Mychairno = 0; 
	int status;
	while(1) {
		/* wait for a car owner to arrive here with money in hand */
		sem_wait(&readywithpayment);
		sem_wait(&mutex4);
		read_pipe(pipe2[0],&Car,&status);
		sem_post(&mutex4);
		printf("ATM: Car %d has arrived with payment. Calling a attender\n",Car);
		sem_wait(&mutex3);
		write_pipe(pipe1[1],MyId);
		write_pipe(pipe1[1],Mychairno);
		sem_post(&mutex3);
		sem_post(&car_ready);
		printf("ATM: Waiting to hear that Car %d has paid to a attender\n",Car);
		sem_wait(&finishedcounter);
		printf("\n\nPayment started\n\n");
		sleep(0.5);
		printf("ATM: Car %d has paid to a attender\n",Car);
		sem_post(&receipt[Car]);
	} 
}