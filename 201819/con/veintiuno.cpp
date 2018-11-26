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
void *
handle_client(void *arg){
        int cfd = *(int *)arg;
        bool fin = false;
        do{
                int con;
                int nbytes = read(cfd,&con,sizeof(int));
                if(nbytes <=0){
                        fin = true;
                }else{
                        char *texto = (char *) malloc(con * sizeof(char));
                        read(cfd,texto,con*sizeof(char));
                        printf("%s\n",texto);
                }
        }while(!fin);
        close(cfd);
        return NULL;
}
int
main(int argc, char *argv[]){
        int fd_socket = socket(AF_INET,SOCK_STREAM,0);
        struct sockaddr_in addr;
        bzero(&addr,sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(8888);
        addr.sin_addr.s_addr = INADDR_ANY;

        int error = bind(fd_socket,(struct sockaddr *)&addr,sizeof(addr));
        if(error!=0){
                perror("ERROR");
                exit(1);
        }
        listen(fd_socket,3);

        do{
                socklen_t tam = sizeof(addr);
                int cliente = accept(fd_socket,(struct sockaddr *)&addr,&tam);
                if(cliente != -1)
                {
                        pthread_t hilo;
                        pthread_create(&hilo,NULL,&handle_client,(void *)&cliente);
                }
        }while(1);
        close(fd_socket);
	return EXIT_SUCCESS;
}
