#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
int
main(int argc, char *argv[]){
        int pid;

        pid = fork();

        if(pid == 0){
                printf("Hola soy el proceso hijo nº: %i", (int) getpid());
                sleep(2);
                execlp("ls","ls",NULL);
                fprintf(stderr,"Error al cargar.\n");
                abort();
        }else{
                printf("Hola soy el proceso padre nº: %i\n",(int) getppid());
                wait(&pid);
        }
        if(WIFEXITED(pid))
                printf("Esto acabo bien hermano con codigo %i\n",WEXITSTATUS(pid));
        else
                printf("Acabo mal esto hermano .\n");
	return EXIT_SUCCESS;
}
