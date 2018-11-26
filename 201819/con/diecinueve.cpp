#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
int
main(int argc, char *argv[]){
        int np = 3, nh = 0, contador = 0;
        int fd[2],nbytes;
        char string[2];

        char readbuf[2];

        pipe(fd);

        pid_t pid = fork();
        if(pid == 0){
                close(fd[0]);
                while(nh<np){
                        contador++;
                        nh++;
                        printf("%i, %i\n",contador, nh);
                }
                string[0] = nh;
                string[1] = contador;
                write(fd[1],string,strlen(string)+1);
                close(fd[1]);
        }else{
                sleep(1);
                close(fd[1]);
                read(fd[0],readbuf,sizeof(readbuf));
                for(int i=0; i<sizeof(readbuf); i++)
                        printf("Data: %i\n",readbuf[i]);
                wait(&pid);
        }
        return EXIT_SUCCESS;
}
