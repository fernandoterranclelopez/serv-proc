#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
int
main(int argc, char *argv[]){
        int fd[2];
        pid_t pid;
        char *cat_args[] = {"cat", "scores",NULL};
        char *grep_args[] = {"grep","oscar",NULL};
        pipe(fd);
        pid = fork();

        if(pid == 0){
                close(fd[1]);
                dup2(fd[0],STDIN_FILENO);
                execvp("grep",grep_args);
                fprintf(stderr,"ERROR");
                abort();
                close(fd[0]);
        }else{
                close(fd[0]);
                dup2(fd[1],STDOUT_FILENO);
                execvp("cat",cat_args);
                fprintf(stderr,"ERROR");
                abort();
                close(fd[1]);
                waitpid(pid,NULL,0);
        }
	return EXIT_SUCCESS;
}
