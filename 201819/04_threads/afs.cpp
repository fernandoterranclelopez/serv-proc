#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define N 2
#define MAX 100000

struct param_imprime {
        char nombre[0x20];
        char apellido[0x20];
        double sueldo;
};

        void *
imprime (void *x)
{
        struct param_imprime p = *((struct param_imprime *) x);
        printf("Nombre: %s\n", p.nombre);

        return NULL;
}

        int
main (int argc, char *argv[])
{

        struct param_imprime p = { "Jose Maria", "Calderon", 550.5 };
        pthread_t mi_hilo;

        pthread_create(&mi_hilo, NULL, &imprime, (void *) &p);

        pthread_join(mi_hilo, NULL);


        fputc('\n', stderr);

        return EXIT_SUCCESS;
}

