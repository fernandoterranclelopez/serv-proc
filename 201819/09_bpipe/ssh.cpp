#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio_ext.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <strings.h>

#define PROMPT "TYPE>"
#define R 0
#define W 1
#define N 0x100
#define MAXIN 0x100000
void handler_child(int signal){
        int status;
        wait(&status);
}
int
main(int argc, char *argv[]){
        int writing[2], reading[2];
        pid_t pid = 0;
        char user[N] = "oscar2710";
        char host[N] = "localhost";
        char input[N];
        char arg[N];
        const char *command = "ssh";
        struct sigaction sa;
        bzero(&sa,sizeof(sa));
        sa.sa_handler = &handler_child;
        sigaction(SIGCHLD,&sa,NULL);
        system("clear");
        printf("Este programa hace tuberias en una conexion ssh.\n");
        printf("Por favor provee datos para establecer la conexion\n");
        sprintf(arg,"%s@%s",user,host);
        printf("Procediendo a %s %s\n", command, arg);
        pipe(writing);
        pipe(reading);

        if(fcntl(reading[R],F_SETFL,O_NONBLOCK)<0)
                exit(2);
        pid = fork();

        if(pid){
                int  nread;
                bool quit = false, writtime = false;
                char pipein[N];
                close(writing[R]);
                close(reading[W]);
                sleep(2);

                do{
                        printf("RECEIVED MSSG: ");
                        writtime = false;


                        while((nread = read(reading[R], pipein,MAXIN)) && !writtime)
                        {
                                switch(nread){
                                        case -1:
                                                if(errno == EAGAIN)//tuberia vacia
                                                {
                                                        writtime = true;
                                                        break;
                                                }else{
                                                        perror("Error de lectura.");
                                                        exit(4);
                                                }
                                                break;
                                        case 0:
                                                //EOF
                                                quit = true;
                                                break;
                                        default:
                                                printf("%s",pipein);
                                                break;
                                }
                        }
                        printf("END MSSG: ");
                        __fpurge(stdin);
                        printf("\n%s",PROMPT);
                        fgets(input,N,stdin);
                        quit = strcasestr(input,"quit");
                        if(!quit)
                                write(writing[W],input,strlen(input)+1);
                        else
                                write(writing[W],"exit",strlen("quit")+1);
                }while(!quit);
                close(writing[W]);
                close(reading[R]);
        }
        else{
                close(writing[W]);
                close(reading[R]);

                dup2(writing[R],STDIN_FILENO);
                dup2(reading[W],STDOUT_FILENO);
                dup2(reading[W],STDERR_FILENO);

                execlp(command,command,"-tt",arg,(char *)NULL);
                fprintf(stderr,"ERROR TO OPEN SSH\n");
                close(writing[R]);
                close(reading[W]);
        }
        return EXIT_SUCCESS;
}
