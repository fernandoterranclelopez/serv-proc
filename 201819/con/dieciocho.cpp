#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int
main(int argc, char *argv[]){
        int np = 3;
        int nh = 0;
        int contador = 0;
        int fd[2],nbytes;
        char readbuf[80];
        pipe(fd);
        pid_t pid;
        char *string = "There´s no time.";
        int longitud = strlen(string)+1;
        pid = fork();
        if(pid == 0){
                close(fd[0]);
                write(fd[1],string,longitud);
                close(fd[1]);
        }else{
                close(fd[1]);
                read(fd[0],readbuf,sizeof(readbuf));
                printf("%s\n",readbuf);
                close(fd[0]);
                wait(&pid);
        }
	return EXIT_SUCCESS;
}
