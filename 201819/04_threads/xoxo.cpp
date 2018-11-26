#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define MAX 1000
void * 
imprime(void *x){
	for(int i=0; i<MAX;i++)
		fputc(*((char *) x), stderr);
	return NULL;
}

int
main(int argc, char *argv[]){

	char x = 'x';
	char o = 'o';
	pthread_t mis_hilos[2];
	pthread_create(&mis_hilos[0],NULL,&imprime,(void *) &x);
	pthread_create(&mis_hilos[1],NULL,&imprime,(void *) &o);
	pthread_join(mis_hilos[0],NULL);
	pthread_join(mis_hilos[1],NULL);

	return EXIT_SUCCESS;
}
