#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#define N 1000
int
main(int argc, char *argv[]){
        struct sockaddr_in socketserver;
        int fd_client;

        fd_client = socket(PF_INET,SOCK_STREAM,0);
        socketserver.sin_family = AF_INET;
        socketserver.sin_addr.s_addr = inet_addr("172.18.35.6");
        socketserver.sin_port = htons(8000);

        if(connect(fd_client,(struct sockaddr *)&socketserver,sizeof(socketserver))!=0){
                perror("cant connect");
                return 1;
        }
        while(1){
                char mensaje[N];
                scanf(" %s",mensaje);
                send(fd_client,mensaje,strlen(mensaje),0);
        }

	return EXIT_SUCCESS;
}
