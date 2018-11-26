#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int
main(int argc, char *argv[]){
        int fd[2];
        pipe(fd);
        pid_t pid;
        pid = fork();
        if(pid == 0){
                close(fd[1]);
                dup2(fd[0],STDIN_FILENO);
                execlp("bc","bc",NULL);
                fprintf(stderr, "ERROR");
                abort();
        }else{
                close(fd[0]);
                FILE *tubo = fdopen(fd[1],"w");
                fprintf(tubo,"102-43\n");
                fflush(tubo);
                close(fd[1]);
                wait(&pid);
        }
	return EXIT_SUCCESS;
}
