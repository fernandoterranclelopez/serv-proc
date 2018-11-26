#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <strings.h>
sig_atomic_t child_status;
void
spawn(char *nombre_programa){
        pid_t pid;

        pid = fork();
        if(pid == 0){
                execlp(nombre_programa,nombre_programa,NULL);
                fprintf(stderr,"An error ocuured\n");
                abort();
        }else
                printf("Im the parent\n");
}

void handle_child(int signal){
        int status;
        wait(&status);
        child_status = status;
}
int
main(int argc, char *argv[]){
        struct sigaction sa;
        bzero(&sa, sizeof(sa));
        sa.sa_handler = &handle_child;
        sigaction(SIGCHLD,&sa,NULL);

        spawn("firefox");


	return EXIT_SUCCESS;
}
