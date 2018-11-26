#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#define N 2
void *
hola(void *arg){
        char *mensaje = (char *)arg;
        for(int i=0; i<strlen(mensaje); i++){
                printf("%c",*(mensaje + i));
                fflush(stdout);
                usleep(1000000);
        }
        printf("\n");
        return NULL;
}
int
main(int argc, char *argv[]){
        char *hello = "oscar";
        char *mundo = "calderon";

        pthread_t mith[N];

        pthread_create(&mith[0],NULL,&hola,(void *)hello);
        pthread_create(&mith[1],NULL,&hola,(void *)mundo);

        for(int i=0; i<N; i++)
                pthread_join(mith[i],NULL);

        return EXIT_SUCCESS;
}
