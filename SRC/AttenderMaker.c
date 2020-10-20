#include <petrolbunk.h>

void AttenderMaker()
{
	int i=1;
	while (i <= fuelMen) {
		pthread_create(&threads[i],NULL,(void *)&Attender,(void *)i);
		i++;
	}
}