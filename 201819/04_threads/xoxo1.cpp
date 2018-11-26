#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define MAX 1000
#define N 2
void * 
imprime(void *x){
	for(int i=0; i<MAX;i++)
		fputc(*((char *) x), stderr);
	return NULL;
}

int
main(int argc, char *argv[]){

	char param[N] = {'x','o'};

	pthread_t mis_hilos[N];
	for(int i=0; i<MAX; i++)
		pthread_create(&mis_hilos[N],NULL,&imprime,(void *) &param[i]);
	for(int i=0; i<MAX; i++)
		pthread_join(mis_hilos[N],NULL);
        fputc('\n',stderr);
	return EXIT_SUCCESS;
}
