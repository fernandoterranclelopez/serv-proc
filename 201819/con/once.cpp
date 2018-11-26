#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#define SIZE 1024

int
main(int argc, char *argv[]){
        int pid;
        int id_seg;
        char *shared_memory;
        id_seg = shmget(IPC_PRIVATE, SIZE,IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
        pid = fork();

        if(pid == 0){
                shared_memory = (char *)shmat(id_seg,(void *)0,0);
                strcpy(shared_memory,"SOY COMO LA POTENCIA"); 
        }else{
                sleep(5);
                shared_memory = (char *)shmat(id_seg,NULL,0);
                printf("Texto en memoria: %s\n",shared_memory);
                shmdt(shared_memory);
                shmctl(id_seg,IPC_RMID,NULL);
                wait(&pid);
        }
	return EXIT_SUCCESS;
}
