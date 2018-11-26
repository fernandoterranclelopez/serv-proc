#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#define R 0 
#define W 1
#define DOWN 0
#define UP 1


int
main(int argc, char *argv[]){
	int fds[2][2];
	pid_t pid;
	int resultado;

	pipe(fds[DOWN]);
	pipe(fds[UP]);

	pid = fork();

	if(pid){
		close(fds[DOWN][R]);
		close(fds[UP][W]);

		write(fds[DOWN][W],"3+4\n",4);
		FILE *tubo = fdopen(fds[UP][R],"r");
		fscanf(tubo, " %i",&resultado);
		write(fds[DOWN][W],"quit\n",5);

		close(fds[DOWN][W]);
		close(fds[UP][R]);
		waitpid(pid,NULL,0);
	}else{
		close(fds[DOWN][W]);
		close(fds[UP][R]);
		
		dup2(fds[DOWN][W],STDIN_FILENO);
		dup2(fds[UP][R], STDOUT_FILENO);

		execlp("bc","bc",NULL);
		fprintf(stderr,"Error\n");
		close(fds[DOWN][R]);
		close(fds[UP][W]);

		abort();
	}
	return EXIT_SUCCESS;
}
