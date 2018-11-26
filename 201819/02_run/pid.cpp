#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int
main(int argc, char *argv[]){
	pid_t child_pid;

	printf("El id del proceso padre es %i\n",(int) getpid());

	child_pid = fork();

	if(child_pid !=0){
		printf("Este es el id del proceso padre: %i\n",(int) getpid());
		printf("El id del proceso hijo : %i\n",(int) child_pid);
	}
	else
		printf("Este es el id del proceso hijo con el id: %i\n",(int) getpid());
	return EXIT_SUCCESS;
}
