//LIBRERIAS
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <malloc.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>

//CONSTANTES
#define N 14
#define NPLAYS 4

//VARIABLES GLOBALES
sig_atomic_t plays_usadas = 0;
sig_atomic_t llama_mama = 0;
sem_t semaforo;
pthread_mutex_t exc = PTHREAD_MUTEX_INITIALIZER;


//FUNCION INICIALIZAR SEMAFORO
void 
iniatialize(int nplays){
	sem_init(&semaforo,0,nplays);
}

//FUNCION HILO
void *
say(void *arg){
	while(!llama_mama){
		sem_wait(&semaforo);
		pthread_mutex_lock(&exc);
		plays_usadas++;
		pthread_mutex_unlock(&exc);
		sleep(rand() % 3 + 1);
		pthread_mutex_lock(&exc);
		plays_usadas--;
		pthread_mutex_unlock(&exc);
		sem_post(&semaforo);
		sleep(rand()%10+1);
	}
}

int
main(int argc, char *argv[]){
	pthread_t boy[N];
	struct timeval tv;
	time_t
	       
		curtime;
	char tiempo[0x20];
	u_int8_t cuanto = 0xFF;

	srand(time(NULL));
	iniatialize(NPLAYS);
	for(int i=0;i<N;i++)
		pthread_create(&boy[i],NULL,&say,(void *) NULL);
	while(cuanto){
		cuanto--;
		gettimeofday(&tv, NULL);
		curtime = tv.tv_sec;
		strftime(tiempo,32,"%T",localtime(&curtime));
		printf("[%s]Usadas: %i                 \r",tiempo,plays_usadas);
		fflush(stdout);
		usleep(500000);
	}
	llama_mama = 1;
	for(int i=0; i<N; i++)
		pthread_join(boy[i],NULL);
	sem_destroy(&semaforo);
	return EXIT_SUCCESS;
}
