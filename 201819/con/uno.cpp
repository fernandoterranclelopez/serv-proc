#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>


int
main(int argc, char *argv[]){

	int id_seg;
	char *shared_memory;
	struct shmid_ds buffer;
	int seg_size;
	const int shared_segment_size = 0x6400;

	id_seg = shmget(IPC_PRIVATE,shared_segment_size,IPC_CREAT| IPC_EXCL | S_IRUSR | S_IWUSR);
	shared_memory = (char *) shmat(id_seg,0,0);
	printf("Memoria cogida en la direccion %p\n",shared_memory);
	shmctl(id_seg,IPC_STAT,&buffer);
	seg_size = buffer.shm_segsz;
	printf("Tamaño del segmento %i\n",seg_size);
	sprintf(shared_memory,"Escribo en la memoria compartida");
	shmdt(shared_memory);

	shared_memory = (char *) shmat(id_seg,(void *) 0x500000,0);
	printf("Direccion de memoria alcanzada: %p\n",shared_memory);
	printf("%s\n",shared_memory);
	shmdt(shared_memory);

	shmctl(id_seg,IPC_RMID,0);
	return EXIT_SUCCESS;
}
