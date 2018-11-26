#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>


int
main(int argc, char *argv[]){
	int id_seg;
	char *shared_memory = NULL;
	struct shmid_ds shmbuffer;
	int segment_size;
	const int shared_segment_size = 0x6400;
        //Creamos la memoria compartida
	id_seg = shmget(IPC_PRIVATE,shared_segment_size,IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	printf("ID segmento = %i\n",id_seg);
        //Alojamos la memoria en el puntero
	shared_memory = (char *) shmat(id_seg,0,0);
	printf("Memoria compartida alojada en la direccion %p\n", shared_memory);
        //Cojemos las estadisticas con shmctl con IPC_STAT y le asignamos a un entero la memoria que coje el campo de shmid_ds que contiene el tamaño y lo imprimos
	shmctl(id_seg,IPC_STAT, &shmbuffer);
	segment_size = shmbuffer.shm_segsz;
	printf("Tamaño del segmento = %i\n", segment_size);
        //Imprimimos en el segmento alojado lo que queremos con sprintf y lo desalojamos
	sprintf(shared_memory,"Hey jude");
	shmdt(shared_memory);
        //Volvemos a alojar otra vez el puntero imprimimos la direccion y el contenido
	shared_memory = (char *) shmat(id_seg,(void *) 0x500000,0);
	printf("Memoria compartida alojada en la direccion %p\n", shared_memory);
        printf("%s\n", shared_memory);
	shmdt(shared_memory);
        //Borramos el id del segmento
	shmctl(id_seg,IPC_RMID,0);

	return EXIT_SUCCESS;
}
