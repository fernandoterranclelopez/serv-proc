#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#define N 10000
void get_home_page(int fd_socket){
        char buffer[N];
        ssize_t numero_carac_leidos;
        sprintf(buffer,"GET /\n");
        write(fd_socket,buffer,strlen(buffer));

        while(1){
                numero_carac_leidos = read(fd_socket,buffer,N);
                if(numero_carac_leidos == 0)
                        return;
                fwrite(buffer,sizeof(char),numero_carac_leidos,stdout);
        }
}
int
main(int argc, char *argv[]){
        int fd_socket;
        struct sockaddr_in name;
        struct hostent *hostinfo;

        fd_socket = socket(PF_INET,SOCK_STREAM,0);
        name.sin_family = AF_INET;
        hostinfo = gethostbyname(argv[1]);

        if(hostinfo == NULL)
                return 1;
        else
                name.sin_addr = *((struct in_addr *) hostinfo->h_addr);
        name.sin_port = htons(80);

        if(connect(fd_socket,(struct sockaddr *)&name, sizeof(struct sockaddr_in)) == -1){
                perror("connect");
                return 1;
        }
        get_home_page(fd_socket);
        return EXIT_SUCCESS;
}
