#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#define N 2
int
main(int argc, char *argv[]){
	int fds[N];
	pid_t pid;

	pipe(fds);
	pid = fork();

	if(pid == (pid_t)0){
		close(fds[1]);
		dup2(fds[0],STDIN_FILENO);
		execlp("sort","sort",NULL);
	}
	else{
		FILE* tubo;
		close(fds[0]);
		tubo = fdopen(fds[1],"w");
		fprintf(tubo,"Auxilio\n");
		fprintf(tubo,"me\n");
		fprintf(tubo,"desmayo\n");
		fprintf(tubo,"callese\n");
		fprintf(tubo,"viejo\n");
		fprintf(tubo,"lesbiano\n");
		fflush(tubo);
		close(fds[1]);
		waitpid(pid,NULL,0);
	}
	return EXIT_SUCCESS;
}
