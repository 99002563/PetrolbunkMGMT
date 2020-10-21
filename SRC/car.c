#include <petrolbunk.h>
void Car(int CarId)
{
	int i,k;

	sem_wait(&max_capacity);
	printf("Car %d enters pump\n",CarId);
	
	sem_wait(&mutex2);
	sem_wait(&mutex_queue);
	if ((free_pumps == 0) || (free_queue_pos < queueSize)) 
    {
		sem_post(&mutex_queue);
		sem_post(&mutex2);
		printf("Car %d deciding petrol quality :)\n",CarId);
		sem_wait(&mutex_queue);
		if (free_queue_pos <= 0) 
        {
			printf("Car %d waiting\n",CarId);
		}
		free_queue_pos--;
		sem_post(&mutex_queue);
		sem_wait(&sem_queue); 

		printf("Car %d is in queue now\n",CarId);
		sem_wait(&sem_pump);
		
		sem_wait(&mutex_queue);
		free_queue_pos++;
		sem_post(&mutex_queue);
		sem_post(&sem_queue);
		printf("Car %d released its queue position\n",CarId);
		
	}
	else 
    {
		sem_post(&mutex_queue);sem_post(&mutex2);sem_wait(&sem_pump);
	}

	/* wait for pump bay to be free */
	sem_wait(&mutex2);
	i = 0;
	while ((pump[i] != -1) && (i < fuelBays))
        i++;
	if (i == fuelBays)
    {
		printf("this is not possible! we are here because at least 1 pump empty!");
		exit(0);
	}
	else 
    {
		pump[i] = CarId;
		free_pumps--; 
		printf("Car %d occupies pump %d. free_pumps = %d\n",CarId,i,free_pumps);
	}
	sem_post(&mutex2);

	sem_wait(&mutex3);
	//	Car get fueled up
	printf("Filling for %d started",CarId);
	write_pipe(pipe1[1],CarId);
	write_pipe(pipe1[1],i);
	sem_post(&mutex3);
	sem_post(&car_ready);
	//Filling done
	sem_wait(&finished[CarId]);
	printf("Filling for %d started",CarId);
	sem_wait(&mutex2);
	free_pumps++;
	pump[i] = -1;
	sem_post(&leave_pump[i]);
	sem_post(&mutex2);
	printf("Car %d left pump %d to atm. free_pumps = %d\n",CarId,i,free_pumps); 
	/*want to pay. */
	sem_wait(&mutex4);
	write_pipe(pipe2[1],CarId);
	sem_post(&mutex4);
	/* Pay starts */
	printf("Car %d ready to pay\n",CarId);

	sem_post(&readywithpayment);
	sem_wait(&receipt[CarId]);

	printf("Car %d paid\n",CarId);
	sem_post(&done[CarId]);
	/* Pay ends */
	sem_post(&max_capacity);
	if (CarId == (totalCars-1))
    {
		for(k=0;k <= (totalCars-1); k++) sem_wait(&done[k]);
		puts("All cars served");
		exit(0);
	}
	else pthread_exit(0);  //exit station
}
