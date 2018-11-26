#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define DOWN 0
#define UP 1
#define R 0
#define W 1
int
main(int argc, char *argv[]){
	int resultado;
	int fd[2][2];
	pid_t pid;
	pipe(fd[DOWN]);
	pipe(fd[UP]);

	pid = fork();

	if(pid){
		close(fd[DOWN][R]);
		close(fd[UP][W]);

		write(fd[DOWN][W],"2+2\n",4);
		FILE* tubo = fdopen(fd[UP][R],"r");
		fscanf(tubo,"%i",&resultado);
		write(fd[DOWN][W],"quit\n",5);

		close(fd[DOWN][W]);
		close(fd[UP][R]);
		waitpid(pid,NULL,0);
	}else{
		close(fd[DOWN][W]);
		close(fd[UP][R]);

		dup2(fd[DOWN][W],STDIN_FILENO);
		dup2(fd[UP][R],STDOUT_FILENO);

		execlp("bc","bc",NULL);
		fprintf(stderr,"ERROR\n");
		close(fd[DOWN][R]);
		close(fd[UP][W]);
		abort();
	}
	return EXIT_SUCCESS;
}
