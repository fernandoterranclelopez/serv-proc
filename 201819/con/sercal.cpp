#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
int
server(int client_socket){
        while(1){
                char *texto;
                int longitud;
                if(read(client_socket,&longitud,sizeof(longitud))==0)
                        return 0;
                texto = (char *) malloc(longitud);
                read(client_socket,texto,longitud);
                printf("%s\n",texto);
                free(texto);
                if(strcmp(texto,"quit"))
                        return 1;
        }
}
int
main(int argc, char *argv[]){
        int fd_socket;
        struct sockaddr_un sockunix;
        const char *const socket_name = argv[1];
        int client_envia_quit_mensaje;

        fd_socket = socket(PF_UNIX,SOCK_STREAM,0);
        sockunix.sun_family = AF_LOCAL;
        strcpy(sockunix.sun_path,socket_name);
        bind(fd_socket,(struct sockaddr *)&sockunix,SUN_LEN(&sockunix));
        listen(fd_socket,4);

        do{
                struct sockaddr_un client_name;
                socklen_t lon_clien_name;
                int fd_client;
                fd_client = accept(fd_socket,(struct sockaddr *) &client_name,&lon_clien_name);
                client_envia_quit_mensaje = server(fd_client);
                close(fd_client);
        }while(!client_envia_quit_mensaje);
        close(fd_socket);
        unlink(socket_name);
	return EXIT_SUCCESS;
}
