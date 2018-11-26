#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define GRANDE 200
#define PORT 8888
#define N 2
#define R 0
#define W 1
//FUNCION GESTORA DE SIGCHLD
sig_atomic_t child_status;
void sigchld_handler(int signal){
        int status;
        wait(&status);
        child_status = status;
}
//GESTIONAMOS LAS RELACIONES CON EL CLIENTE
void gestionar_cliente(int fd_client){
        //HAcemos pipes bidimensionales
        int fd[N][N];
        pipe(fd[0]);
        pipe(fd[1]);
        pid_t son;
        son = fork();

        if(son){
                //Parent proceso
                close(fd[R][R]);
                close(fd[W][W]);
                //Alojamos en una lista lo que nos envia el cliente
                char *lista = (char *)malloc(200);
                //Lo leemos
                int nbytes = recv(fd_client,lista,200,0);
                lista[nbytes] = '\0';
                //Escribimos la lista ppara que lo ordene 
                write(fd[R][W],lista,sizeof(char)*nbytes);
                close(fd[R][W]);
                //Leeemos la lista enviada
                read(fd[W][R],lista,sizeof(char) * nbytes);
                //La enviamos al cliente
                send(fd_client,lista,nbytes,0);
                free(lista);
                close(fd[R][W]);
        }else{
                //Proceso hijo aqui ordena la lista
                close(fd_client);
                close(fd[R][W]);
                close(fd[W][R]);

                dup2(fd[R][R],STDIN_FILENO);
                dup2(fd[W][W],STDOUT_FILENO);

                execlp("sort","sort",NULL);
                fprintf(stderr,"ERROR\n");
                close(fd[R][R]);
                close(fd[W][W]);
                abort();
        }
}
int
main(int argc, char *argv[]){
        //SOCKET
        struct sockaddr_in addr;
        int fd_socket;
        int act = 1;
        //OPCION GETOPT
        int opcion;
        const char *const short_option = "lp";
        int port;
        //GESTOR SIGCHLD
        struct sigaction sa;
        bzero(&sa,sizeof(sa));
        sa.sa_handler = &sigchld_handler;
        sigaction(SIGCHLD,&sa,NULL);
        //CRAEAR EL SOCKET
        fd_socket = socket(AF_INET,SOCK_STREAM,0);
        //COGER OPCION
        opcion = getopt(argc,argv,short_option);
       //CONFIGURAR SOCKET
        if(opcion == 'l'){
                addr.sin_family = AF_INET;
                addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
                addr.sin_port = htons(PORT);
        }else
                if(opcion == -1){
                        addr.sin_family = AF_INET;
                        addr.sin_addr.s_addr = htonl(INADDR_ANY);
                        addr.sin_port = htons(PORT);
                }
        //ACTIVAMOS SOCKET
        setsockopt(fd_socket,SOL_SOCKET,SO_REUSEADDR,&act,sizeof(act));
        //Dar direccion
        if(bind(fd_socket,(struct sockaddr *)&addr,sizeof(addr))!=0){
                perror("ERROR");
                return 1;
        }
        //ESCUCHAR
        if(listen(fd_socket,5)!=0){
                perror("ERROR");
                return 1;
        }

        do{
                socklen_t size = sizeof(addr);
                //Aceptamos las conexiones
                int cliente_fd = accept(fd_socket,(struct sockaddr *)&addr,&size);

                pid_t pid = fork();
                if(pid){
                        //Padre cierrra cliente
                        close(cliente_fd);
                }else{
                        //Hijo cerramos las entrada y salida estandar
                        close(STDIN_FILENO);
                        close(STDOUT_FILENO);
                        close(fd_socket);
                        //gestionamos cliente
                        gestionar_cliente(cliente_fd);
                        close(cliente_fd);
                        return 0;
                }
        }while(1);
        close(fd_socket);
	return EXIT_SUCCESS;
}
