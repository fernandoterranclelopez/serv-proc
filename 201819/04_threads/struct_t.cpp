#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define N 2
struct Persona{
	char nombre[0x20];
	char apellidos[0x20];
	double salario;
};

void *
imprime(void *algo){
	struct Persona p = *((struct Persona *)algo);
	printf("%s\n",p.nombre);
	printf("%s\n",p.apellidos);
	printf("%.2lf\n",p.salario);
	return NULL;
}
int
main(int argc, char *argv[]){
	pthread_t hilo[N];
	struct 	Persona p[N] = {
		{
			"Oscar",
			"Calderon",
			1002.23
		}
		,{
			"Bart",
			"Simpson",
			1343.21
		}
	};

	for(int i=0; i<N; i++)
		pthread_create(&hilo[i], NULL, &imprime,(void *)&p[i]);
	for(int i=0; i<N; i++)
		pthread_join(hilo[i],NULL);
	fputc('\n',stderr);
	return EXIT_SUCCESS;
}
