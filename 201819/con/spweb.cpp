#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
void
obtener_pagina(int fd){
        char buffer[10000];
        ssize_t nbytes;
        sprintf(buffer,"GET /\n");
        write(fd,buffer,strlen(buffer));
        while(1){
                nbytes = read(fd,buffer,strlen(buffer));
                if(nbytes == 0)
                        return;
                fwrite(buffer,sizeof(char),nbytes,stdout);
        }
}
int
main(int argc, char *argv[]){
        int fd_socket; 
        struct sockaddr_in sockin;
        struct hostent *hostinfo;

        fd_socket = socket(PF_INET,SOCK_STREAM,0);
        sockin.sin_family = AF_INET;
        hostinfo = gethostbyname(argv[1]);

        if(hostinfo == NULL){
                printf("No hay host\n");
                return 1;
        }else
                sockin.sin_addr = *((struct in_addr *) hostinfo->h_addr);
        sockin.sin_port = htons(80);
        if(connect(fd_socket,(struct sockaddr *)&sockin,sizeof(struct sockaddr_in)) == -1){
                perror("connect");
                return 1;
        }
        obtener_pagina(fd_socket);
	return EXIT_SUCCESS;
}
