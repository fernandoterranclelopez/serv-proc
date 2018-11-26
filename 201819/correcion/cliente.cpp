#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio_ext.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define N 40
#define GRANDE 200

int
main(int argc, char *argv[]){
        //Palabra y lista donde se almacena
        char palabra[N];
        char buffer[GRANDE];
        memset(buffer,'\0',sizeof(buffer));
        //estructura socket
        struct sockaddr_in client_sk;
        int fd_server;
        fd_server = socket(AF_INET,SOCK_STREAM,0);
        client_sk.sin_family = AF_INET;
        client_sk.sin_addr.s_addr = inet_addr("127.0.0.1");
        client_sk.sin_port = htons(8888);
        //Nos conectamos al server
        if(connect(fd_server,(struct sockaddr *)&client_sk,sizeof(client_sk))!=0){
                perror("ERROR AL CONECTAR");
                return 1;
        }
        bool value = false;
        //PEdimos la lista de palabras
        do{
                __fpurge(stdin);
                int longitud = 0;
                printf("Palabra(quit para salir): ");
                fgets(palabra,N,stdin);
                longitud = strlen(palabra);
                if(strcmp(palabra,"quit\n") == 0)
                        value = true;
                //Concatenamos cada palabra a la lista
                strncat(buffer,palabra,longitud);
        }while(value == false);
        //Enviamos la lista al servidor
        send(fd_server,buffer,strlen(buffer),0);
        //Recibimos la lista y la imprimimos
        recv(fd_server,buffer,strlen(buffer),0);
        printf("%s",buffer);
        close(fd_server);



	return EXIT_SUCCESS;
}
