#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#define N 2
int
main(int argc, char *argv[]){
	int resultado;
	int fds[N];
	pid_t pid;

	pipe(fds);
	pid = fork();

	if(pid == (pid_t) 0){
		close(fds[1]);
		dup2(fds[0],STDIN_FILENO);
		execlp("bc","bc",NULL);
		fprintf(stderr,"Error\n");
		abort();
	}
	else{
		FILE *dc;
		close(fds[0]);
		dc = fdopen(fds[1],"w");
		fprintf(dc,"23+12\n");
		fflush(dc);
		close(fds[1]);
		waitpid(pid,NULL,0);
	}

	return EXIT_SUCCESS;
}
