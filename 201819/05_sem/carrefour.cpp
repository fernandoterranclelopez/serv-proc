#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>
#include <malloc.h>
#include <pthread.h>
#include <time.h>
#define NCAJAS 7
#define SIZEROW 50
sem_t controller;
sig_atomic_t cajas_ocupadas = 0;
sig_atomic_t fin = 0;
pthread_mutex_t critic = PTHREAD_MUTEX_INITIALIZER;

void 
init(int cajas_totales){
	sem_init(&controller, 0, cajas_totales);
}
void *
control(void *arg){
	while(!fin){
		sem_wait(&controller);

		pthread_mutex_lock(&critic);
		cajas_ocupadas++;
		pthread_mutex_unlock(&critic);

		sleep(3);

		pthread_mutex_lock(&critic);
		cajas_ocupadas--;
		pthread_mutex_unlock(&critic);

		sem_post(&controller);

		sleep(1);
	}
}
int
main(int argc, char *argv[]){
	pthread_t clientes[SIZEROW]; 
	init(NCAJAS);
	int contador = 256;
	for(int i=0; i<SIZEROW; i++)
		pthread_create(&clientes[i],NULL,&control,(void *) NULL);
	while(contador){
		contador--;
		printf("Hay %i cajas usadas                 \r", cajas_ocupadas);
		fflush(stdout);
		sleep(1);
	}
	for(int i=0; i<NCAJAS; i++)
		pthread_join(clientes[i],NULL);
	sem_destroy(&controller);
	return EXIT_SUCCESS;
}
