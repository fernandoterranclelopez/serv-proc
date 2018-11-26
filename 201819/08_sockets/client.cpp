#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
void
escribir_text(int fd_socket, const char *text){
        int lenght = strlen(text)+1;
        write(fd_socket,&lenght,sizeof(lenght));
        write(fd_socket, text,lenght);
}
int
main(int argc, char *argv[]){
        int fd_socket;
        const char *const socket_name = argv[1];
        const char *const mensaje = argv[2];
        struct sockaddr_un name;

        fd_socket = socket(PF_LOCAL,SOCK_STREAM,0);
        name.sun_family = AF_LOCAL;
        strcpy(name.sun_path,socket_name);
        connect(fd_socket,(struct sockaddr *)&name,SUN_LEN(&name));
        escribir_text(fd_socket,mensaje);
        close(fd_socket);
	return EXIT_SUCCESS;
}
