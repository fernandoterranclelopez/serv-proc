#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/shm.h>
int
main(int argc, char *argv[]){
        int id_segmento;
        int tamano_seg = 0x1000;
        struct shmid_ds shmbuffer;
        char *shared_memory = NULL;

        id_segmento = shmget(IPC_PRIVATE,tamano_seg, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
        shared_memory = (char *) shmat(id_segmento,0,0);
        shmctl(id_segmento,IPC_STAT,&shmbuffer);
        int segsz = shmbuffer.shm_segsz;
        sprintf(shared_memory,"HOAL");
        shmdt(shared_memory);
        shared_memory = (char *) shmat(id_segmento,(void *)0x5000000,0);
        printf("%s\n",shared_memory);
        shmdt(shared_memory);
        shmctl(id_segmento,IPC_RMID,0);
	return EXIT_SUCCESS;
}
