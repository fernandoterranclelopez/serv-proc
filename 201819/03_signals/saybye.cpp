#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
sig_atomic_t continuo = 1;

void 
tell_me(int signal_number){
	continuo = 0;
}


int
main(int argc, char *argv[]){
	struct sigaction sa;
	bzero(&sa,sizeof(sa));
	sa.sa_handler = &tell_me;
	sigaction(SIGINT,&sa,NULL);
	printf("PID = %i\n", (int) getpid());
	while(continuo)
		sleep(1);
	printf("Limpio\n");
	return EXIT_SUCCESS;
}
