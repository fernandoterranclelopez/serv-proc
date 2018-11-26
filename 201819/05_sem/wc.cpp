#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>
#include <malloc.h>
#include <pthread.h>
#include <time.h>

#define NWC 8
#define N 40
sig_atomic_t vateres_ocupados = 0;
sig_atomic_t fin = 0;
sem_t sem;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void
init(int nwc){
        sem_init(&sem,0,nwc);
}
void *
paso(void* arg){
 while(!fin){
         sem_wait(&sem);
         pthread_mutex_lock(&mutex);
         vateres_ocupados++;
         pthread_mutex_unlock(&mutex);
         sleep(3);
         pthread_mutex_lock(&mutex);
         vateres_ocupados--;
         pthread_mutex_unlock(&mutex);
         sem_post(&sem);
 }
}
int
main(int argc, char *argv[]){
        pthread_t cola[N];
        int contador = 30;
        init(NWC);
        for(int i=0; i<N; i++)
                pthread_create(&cola[i],NULL,&paso,(void*)NULL);
        while(contador!=0){
                contador--;
                printf("Hay %i wc ocupados.           \r", vateres_ocupados);
                fflush(stdout);
                sleep(1);
        }
        for(int i=0; i<N; i++)
                pthread_join(cola[i],NULL);
        sem_destroy(&sem);
	return EXIT_SUCCESS;
}
