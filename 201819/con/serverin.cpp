#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
int
main(int argc, char *argv[]){
        int fd_socket;
        struct sockaddr_in socketin;
        int act = 1;

        fd_socket = socket(PF_INET,SOCK_STREAM,0);
        socketin.sin_family = AF_INET;
        socketin.sin_addr.s_addr = INADDR_ANY;
        socketin.sin_port = htons(8000);

        setsockopt(fd_socket,SOL_SOCKET,SO_REUSEADDR,&act, sizeof(act));

        if(bind(fd_socket,(struct sockaddr *)&socketin,sizeof(socketin)) != 0){
                perror("FALLO AL ABRIR EL SOCKET");
                return 1;
        }
        printf("IM LISTENING\n");
        listen(fd_socket,100);

        struct sockaddr_in socketclient;
        unsigned int tamdirec;
        int cliente = accept(fd_socket,(struct sockaddr *)&socketclient,&tamdirec);
        send(cliente,"Hola bro",8,0);
        send(cliente,":V\n",4,0);


        char *mensaje = (char *) malloc(1000);

        while(1){
                int nbytes = recv(cliente,mensaje,1000,0);
                if(nbytes <= 0){
                        perror("Disconect user\n");
                        return 0;
                }
                mensaje[nbytes] = '\0';
                printf("Me llegaron %i bytes con %s\n",nbytes,mensaje);
        }
        free(mensaje);
        return EXIT_SUCCESS;
}

