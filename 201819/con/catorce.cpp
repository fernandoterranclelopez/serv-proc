#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <strings.h>
#include <sys/wait.h>
int bandera = 1;
void handler(int signum){
        if(signum == SIGUSR1)
                printf("recibi señal de mi padre %i\n",signum);
        else
                printf("recibi señal de mi hijo %i\n", signum);
	bandera = 0;
}
int
main(int argc, char *argv[]){
	int status;
	struct sigaction sa;
	bzero(&sa,sizeof(sa));
	sa.sa_handler = &handler;
	sigaction(SIGUSR1,&sa,NULL);
	sa.sa_handler = &handler;
	sigaction(SIGUSR2,&sa,NULL);
	pid_t pid = fork();

	if(pid == 0){
		printf("Soy el hijo y espero a mi padre, mi pid = %i\n",(int)getpid());
		while(bandera);
		kill(getppid(),SIGUSR2);
	}else{
		printf("Soy padre, mi pid es %i\n", (int)getppid());
		sleep(3);
		kill(getpid(),SIGUSR1);
		wait(&status);
		printf("mi  hijo acabo con un estado: %i\n",status);
	}
	return EXIT_SUCCESS;
}
