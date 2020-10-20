#include <petrolbunk.h>

void Attender(int number) {
	int myCar, myPump, status;
	while(1) {

		printf("Attender %d: waiting for a car\n",number);
		/* we sleep till there is there a car on a pump
		   or there is a call from the atm */
		sem_wait(&car_ready);

		/* obtain customerid and pump_no securely */
		sem_wait(&mutex3);

		read_pipe(pipe1[0],&myCar,&status);
		read_pipe(pipe1[0],&myPump,&status);
		sem_post(&mutex3);

		if (myCar != -1) {
			serveCar(myCar,number,myPump);
		}
		else {
			acceptPayment(); 
		}
	} 
}