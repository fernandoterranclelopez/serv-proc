#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
void *
primos(void *arg){
	int candidato = 2;
	int n = *((int *)arg);

	while(1){
		int factor;
		int es_primo = 1;

		for(factor = 2; factor<candidato; ++factor)
			if(candidato%factor == 0){
				es_primo = 0;
				break;
			}
			if(es_primo){
				if(--n == 0)
					return (void *) candidato;
			}
		++candidato;
	}
	return NULL;
}

int
main(int argc, char *argv[]){
	pthread_t hilo;
	int cual;
	int primo;
        printf("Que numero quieres saber con su primo correspondiente: ");
	scanf(" %i",&cual);
	pthread_create(&hilo,NULL,&primos,(void *) &cual);
	pthread_join(hilo,(void **)&primo);

	printf("el %iº numero primo es el %i\n",cual, primo);
	return EXIT_SUCCESS;
}
