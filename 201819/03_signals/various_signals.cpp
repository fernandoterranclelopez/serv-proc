#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <strings.h>

sig_atomic_t sign = 0;
void
handler_sigterm(int signal){
	sign = 1;
}
void
handler_sigint(int signal){
	sign = 2;
}
int
main(int argc, char *argv[]){
	struct sigaction sa;
	bzero(&sa,sizeof(sa));
	sa.sa_handler = &handler_sigterm;
	sigaction(SIGTERM,&sa,NULL);
	sa.sa_handler = &handler_sigint;
	sigaction(SIGINT,&sa,NULL);

	printf("PID: %i\n", (int) getpid());

	while(sign == 0)
		sleep(1);
	printf("La funcion de salida  es: %s.\n", sign == 1 ? "sigterm" : "sigint");

	return EXIT_SUCCESS;
}
