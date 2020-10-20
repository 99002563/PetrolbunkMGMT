#include <petrolbunk.h>

void CarMaker()
{
	int i=0;
	while (i < totalCars) {
		sleep(rand()%3);
		pthread_create(&threads[i+fuelMen],NULL,(void *)&Car,(void *)i);
		printf("Car %d born\n",i );
		i++;
	}
}
