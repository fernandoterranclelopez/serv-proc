#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#define N 3
struct Tparametros{
        int index;
        int escalar;
        int matriz[N][N];
};

void iniciar(int m[N][N]){
        for(int f=0; f<N; f++)
                for(int c=0; c<N; c++)
                        m[f][c] = rand()%10;
}

void *funcion(void *arg){
        struct Tparametros p = *(struct Tparametros *) arg;
        for(int f=0; f<N; f++){
                printf("Hilo %i multiplicando fila %i\n",p.index,f);
                for(int c=0;c<N; c++){
                        p.matriz[f][c] = p.matriz[f][c] * p.escalar;
                        usleep(1000000);
                }
        }
}
int
main(int argc, char *argv[]){
        srand(time(NULL));
        struct Tparametros par[2];
        par[0].index = 1;
        par[0].escalar = 5;
        iniciar(par[0].matriz);
        par[1].index = 2;
        par[1].escalar = 10;
        iniciar(par[1].matriz);
        pthread_t mh1,mh2;
        pthread_create(&mh1,NULL,&funcion,(void *)&par[0]);
        pthread_create(&mh2,NULL,&funcion,(void *)&par[1]);
        pthread_join(mh1,NULL);
        pthread_join(mh2,NULL);
        return EXIT_SUCCESS;
}
