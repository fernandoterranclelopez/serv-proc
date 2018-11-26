#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <strings.h>
#define GRANDE 0x10000

sig_atomic_t child_exit_status;
void sigchl_handler(int signal){
        int status;
        wait(&status);
        child_exit_status = status;
}

int
main(int argc, char *argv[]){
        //USAMOS EL SOCKET
        struct sockaddr_in addr;
        int fd_socket;
        int opcion;
        //SIGCHLD
        struct sigaction sa;
        bzero(&sa,sizeof(sa));
        sa.sa_handler = &sigchl_handler;
        sigaction(SIGCHLD,&sa,NULL);
        //OPCIONES
        const char *const short_option = "l";
        const struct option long_option = {"loopback",0,NULL,'l'};
        int act = 1;

        opcion = getopt(argc,argv,short_option);

        fd_socket = socket(AF_INET,SOCK_STREAM,0);

        if(opcion == 'l'){
                addr.sin_family = AF_INET;
                addr.sin_addr.s_addr = INADDR_LOOPBACK;
                addr.sin_port = htons(8000);
        }else
                if(opcion == -1){
                        addr.sin_family = AF_INET;
                        addr.sin_addr.s_addr = INADDR_ANY;
                        addr.sin_port = htons(8000);
                }

        setsockopt(fd_socket,SOL_SOCKET,SO_REUSEADDR,&act,sizeof(act));

        if(bind(fd_socket,(struct sockaddr*)&addr,sizeof(addr))!=0) {
                perror("Cant connect");
                return EXIT_FAILURE;
        }
        if(listen(fd_socket,5)!=0){
                perror("ERROR TO LISTEN");
                return EXIT_FAILURE;
        }
        //Gestionamos cualquier proceso
        while(1){
                struct sockaddr_in cliente_sk;
                socklen_t sk_length;
                int client_conexion;
                int writing[2];
                int reading[2];
                int nbytes;
                sk_length = sizeof(cliente_sk);
                pipe(writing);
                pipe(reading);
                pid_t pid;
                char lista[GRANDE];
                client_conexion = accept(fd_socket,(struct sockaddr *)&cliente_sk,&sk_length);

                pid = fork();
                if(pid == 0){
                        close(client_conexion);
                        close(writing[1]);
                        close(reading[0]);
                        dup2(writing[0],STDIN_FILENO);
                        dup2(reading[1],STDOUT_FILENO);
                        execlp("sort","sort",NULL);
                        close(writing[0]);
                        close(reading[1]);
                        fprintf(stderr,"ERROR");
                        abort();
                }else{
                        close(writing[0]);
                        close(reading[1]);
                        recv(client_conexion,lista,GRANDE,0);
                        write(writing[1],lista,GRANDE);
                        close(writing[1]);
                        read(reading[0],lista,GRANDE);
                        printf("%s",lista);
                        close(reading[0]);
                }
        }
        close(fd_socket);
        return EXIT_SUCCESS;
}
