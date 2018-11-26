#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
int
main(int argc, char *argv[]){
        int fd[4];
        int status;

        char *cat_args[] = {"cat","scores",NULL};
        char *grep_args[] = {"grep","oscar",NULL};
        char *cut_args[] = {"cut","-b","1-5",NULL};
        pid_t pid;

        pipe(fd);
        pid = fork();

        if(pid == 0){
                for(int i=0; i<4;i++)
                        if(i!=1)
                                close(fd[i]);
                dup2(fd[1],STDOUT_FILENO);
                execvp(*cat_args,cat_args);
                fprintf(stderr,"ERROR");
                abort();
                close(fd[1]);

        }else{
                pid = fork();
                if(pid == 0){
                        for(int i=0; i<4; i++)
                                if(i!=0)
                                        close(fd[i]);
                        dup2(fd[2],STDIN_FILENO);
                        execvp(*grep_args,grep_args);
                        fprintf(stderr,"ERROR");
                        abort();
                        close(fd[0]);

                }else{
                        pid = fork();
                        if(pid == 0){
                                for(int i=0; i<4; i++)
                                        if(i!=2)
                                                close(fd[i]);
                                dup2(fd[2],STDIN_FILENO);
                                execvp(*cut_args,cut_args);
                                fprintf(stderr,"ERROR");
                                abort();
                                close(fd[2]);
                        }
                }
        }
        return EXIT_SUCCESS;
}
