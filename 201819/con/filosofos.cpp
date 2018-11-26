#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <malloc.h>
struct TParam{
        int posicion;
        int contador;
        sem_t *tenedor;
};
pthread_mutex_t lock  = PTHREAD_MUTEX_INITIALIZER;
void *filosofo(void *arg);
void comer(int pos){
        printf("Filosofo %i comiendo.\n",pos);
}
void pensar(int pos){
        printf("Filosofo %i pensar.\n",pos);
}

void iniciar_semaforo( sem_t *tenedor, int numero_tenedores){
        for(int i=0; i<numero_tenedores;i++)
                sem_init(&tenedor[i], 0,1);
}
void correr_hilo(pthread_t *hilos, sem_t *tenedor,int num_filosofos){
        for(int i=0; i<num_filosofos; i++){
                struct TParam *arg = (struct TParam *)malloc(sizeof(struct TParam ));
                arg->posicion = i;
                arg->contador = num_filosofos;
                arg->tenedor = tenedor;
                pthread_create(&hilos[i],NULL,&filosofo,(void *)arg);
        }
}

void *filosofo(void *arg){
        struct TParam par = *(struct TParam*)arg;
        for(int i=0; i<3; i++){
                pensar(par.posicion);
                pthread_mutex_lock(&lock);
                sem_wait(&par.tenedor[par.posicion]);
                sem_wait(&par.tenedor[(par.posicion+1) % par.contador]);
                comer(par.posicion);
                sem_post(&par.tenedor[par.posicion]);
                sem_post(&par.tenedor[(par.posicion +1)%par.contador]);
                pthread_mutex_unlock(&lock);
                sleep(1);
        }
        pensar(par.posicion);
        return NULL;
}
int
main(int argc, char *argv[]){
        int numfil = 5;
        sem_t tenedor[numfil];
        pthread_t filosofos[numfil];
        iniciar_semaforo(tenedor,numfil);
        correr_hilo(filosofos,tenedor,numfil);
        for(int i=0; i<numfil; i++)
                pthread_join(filosofos[i],NULL);
	return EXIT_SUCCESS;
}
