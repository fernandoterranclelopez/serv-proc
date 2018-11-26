#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define READ 0
#define WRITE 1
#define N 2
#define SIZE 0x100
int
main(int argc, char *argv[]){
        pid_t pid;
        int fd[N],nbytes;
        char *mensaje_hijo = "as 4 da manha eu no devia ir mas a cabeça so diz go go go";
        char mensaje_recibido[SIZE];
        int lon = strlen(mensaje_hijo);
        pipe(fd);
        pid = fork();
        if(pid == 0){
                close(fd[READ]);
                write(fd[WRITE],mensaje_hijo,strlen(mensaje_hijo));
                close(fd[WRITE]);
        }else{
                close(fd[WRITE]);
                read(fd[READ],mensaje_recibido,lon);
                printf("%s\n",mensaje_recibido);
                close(fd[READ]);
        }
	return EXIT_SUCCESS;
}
