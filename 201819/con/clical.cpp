#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
void
escribir_mensaje(int fd_socket, const char *text){
        int longitud = strlen(text)+1;
        write(fd_socket,&longitud,sizeof(longitud));
        write(fd_socket,text,longitud);
}
int
main(int argc, char *argv[]){
        struct sockaddr_un client_sck;
        int fd_client;
        const char *const socket_name = argv[1];
        const char *const message = argv[2];
        fd_client = socket(PF_LOCAL,SOCK_STREAM,0);
        client_sck.sun_family = AF_LOCAL;
        strcpy(client_sck.sun_path,socket_name);
        connect(fd_client,(struct sockaddr *)&client_sck,SUN_LEN(&client_sck));
        escribir_mensaje(fd_client,message);
        close(fd_client);
	return EXIT_SUCCESS;
}
