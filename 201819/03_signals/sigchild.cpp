#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/wait.h>

sig_atomic_t child_exit_status;

void
limpiar_proceso_hijo(int signal){
	int estado;
	wait(&estado);
	child_exit_status = estado;
}
int
main(int argc, char *argv[]){
	struct sigaction sa;
	pid_t id_proceso_hijo;
	bzero(&sa,sizeof(sa));
	sa.sa_handler = &limpiar_proceso_hijo;
	sigaction(SIGCHLD,&sa,NULL);

	id_proceso_hijo = fork();

	if(id_proceso_hijo != 0){
		printf("ID child = %i\n",(int) getppid());
		sleep(60);
	}
	else{
		printf("ID parent = %i\n", (int) getpid());
		sleep(60);
	}
	return EXIT_SUCCESS;
}
