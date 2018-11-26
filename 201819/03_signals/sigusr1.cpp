#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
sig_atomic_t sigusr1_count = 0;

void 
handler(int signal_number){
	++sigusr1_count;
}


int
main(int argc, char *argv[]){
	struct sigaction sa;
	bzero(&sa,sizeof(sa));
	sa.sa_handler = &handler;
	sigaction(SIGUSR1,&sa,NULL);
	printf("PID = %i\n", (int) getpid());
        sleep(10);
	printf("SIGUSR1 fue alcanzado %i veces\n", sigusr1_count);
	return EXIT_SUCCESS;
}
