#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
void 
handle_server(int fd ){
        char *texto = "hola";
        int count = strlen(texto);
        write(fd,&count,sizeof(int));
        write(fd,texto,count * sizeof(char));
        printf("Envie un ,ensaje\n");
}
int
main(int argc, char *argv[]){
        int socket_fd = socket(AF_INET,SOCK_STREAM,0);
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        addr.sin_port = htons(8888);

        socklen_t size = sizeof(addr);
        int server_fd = connect(socket_fd,(struct sockaddr *)&addr,size);
        if(server_fd != -1)
                handle_server(socket_fd);
        else
                printf("OUT\n");
        close(socket_fd);
	return EXIT_SUCCESS;
}
