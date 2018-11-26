#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

int
server(int cs){
        while(1){
                char *text;
                int length;
                if(read(cs,&length,sizeof(length))==0)
                        return 0;
                text = (char *) malloc(length);
                read(cs,text,length);
                printf(" %s\n",text);
                free(text);

                if(strcmp(text,"quit"))
                        return 1;
        }
}
int
main(int argc, char *argv[]){
        const char *const socket_name = argv[1];
        int fd_socket;
        struct sockaddr_un name;
        int client_sent_quit_message;

        fd_socket = socket(PF_UNIX, SOCK_STREAM,0);
        name.sun_family = AF_LOCAL;
        strcpy(name.sun_path,socket_name);
        bind(fd_socket, (struct sockaddr *)&name, SUN_LEN(&name));
        listen(fd_socket,5);

        do{
                struct sockaddr_un name_client;
                socklen_t client_len;
                int client_message;
                client_message = accept(fd_socket,(struct sockaddr *) &name_client, &client_len);
                client_sent_quit_message = server(client_message);
                close(client_message);
        }while(!client_sent_quit_message);
        close(fd_socket);
        unlink(socket_name);
        return EXIT_SUCCESS;
}
