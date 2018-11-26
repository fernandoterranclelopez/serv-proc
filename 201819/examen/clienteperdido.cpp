#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio_ext.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define GRANDE 0x10000
#define N 0x100
int
main(int argc, char *argv[]){
        //Variables
        char palabra[N];
        char buffer[GRANDE];
        int longitud;
        int i=0;
        struct sockaddr_in addr;
        int fd_cliente;
        int num = 1;
        fd_cliente = socket(AF_INET,SOCK_STREAM,0);
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        addr.sin_port = htons(8000);

        if(connect(fd_cliente,(struct sockaddr*)&addr,sizeof(addr))!=0){
                perror("ERROR AL CONECTAR");
                exit(1);
        }
        bool value = false;
        do{
                __fpurge(stdin);
                printf("Palabra: ");
                scanf(" %s",palabra);
                if(strcmp(palabra,"quit"))
                        value = true;
                else{
                        longitud = strlen(palabra);
                        palabra[longitud-1] = '\n';
                        strncat(buffer,palabra,longitud);
                }
        }while(value == false);
        send(fd_cliente,buffer,GRANDE,0);
        close(fd_cliente);
        return EXIT_SUCCESS;
}
