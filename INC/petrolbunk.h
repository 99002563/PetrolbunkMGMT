#ifndef __PETROLBUNK_H_
#define __PETROLBUNK_H_
    #include<semaphore.h>
    #include<pthread.h>
    #include<unistd.h>
    #include<stdio.h>
    #include<stdlib.h>

    #define totalCars 100000
    #define fuelMen 3
    #define maxCars 7
    #define fuelBays 3
    #define queueSize 4
    #define threadSize 100008

    pthread_t threads[threadSize], atm;
    sem_t max_capacity;
    int free_pumps = fuelBays;
    sem_t mutex2,mutex3, mutex4;
    int free_queue_pos = queueSize, pipe1[2], pipe2[2];
    sem_t mutex_queue;
    sem_t sem_queue;
    sem_t sem_pump;
    int pump[fuelBays];
    sem_t car_ready;
    sem_t finished[totalCars];
    sem_t done[totalCars];
    sem_t finishedcounter;
    sem_t leave_pump[fuelBays];
    sem_t readywithpayment;
    sem_t receipt[totalCars];

    void Attender(int number);
    void ATM();
    void Car(int CarId);
    void serveCar(int myCar,int number,int myPump);
    void AttenderMaker();
    void acceptPayment();
    void CarMaker();

#endif
