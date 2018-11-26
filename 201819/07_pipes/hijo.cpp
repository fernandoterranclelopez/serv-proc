#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#define R 0
#define W 1

pid_t son;



int 
main(int argc, char *argv[]){
	int fds[2];
	FILE* tuberia;

	pipe(fds);
	son = fork();

	if(son){
		close(fds[R]);
		tuberia = fdopen(fds[W],"w");
		fprintf(tuberia,"Ich bin so schön verstrahlt. %i",EOF);
		close(fds[W]);
		wait(&son);
	}
	else{
		close(fds[W]);
		tuberia = fdopen(fds[R],"r");
		execl("./frase","./frase",NULL);
		fprintf(stderr,"I can´t access.\n");
		abort();
		close(fds[R]);
	}
	return EXIT_SUCCESS;
}
