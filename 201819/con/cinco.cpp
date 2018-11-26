#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define N 5
struct Trandom{
        int random;
        int indice;
};

int aleatorio[N];


void *
hilo(void *arg){
        struct Trandom est = *(struct Trandom *)arg;
        int cont = est.indice;
        srand(time(NULL)+cont);
        aleatorio[cont] = (rand()% est.random)+1;
        printf("numero aleatorio:(%i) %i\n",cont, aleatorio[cont]);
        cont++;
        return NULL;
}
int
main(int argc, char *argv[]){
        pthread_t thr[N];
        struct Trandom tr[N];
        for(int i=0;i<N; i++){
        tr[i].random = 10;
        tr[i].indice = i;
        }

        for(int i=0; i<N; i++)
                pthread_create(&thr[i],NULL,&hilo,(void *)&tr[i]);
        for(int i=0; i<N; i++)
                pthread_join(thr[i],NULL);
        int total = 0;
        for(int i=0; i<N; i++)
                total += aleatorio[i];
        printf("%i\n",total);
	return EXIT_SUCCESS;
}
