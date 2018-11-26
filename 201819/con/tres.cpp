#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#define FILE_LENGTH 0x100

int
main(int argc, char *argv[]){
	int fd;
	void *fm;
	int numero;

	fd = open(argv[1], O_RDWR, S_IRUSR| S_IWUSR);
	fm = mmap(0,FILE_LENGTH, PROT_WRITE | PROT_READ, MAP_SHARED, fd,0);
	close(fd);
	sscanf((char*)fm,"%i",&numero);
	printf("numero: %i\n",numero);
	sprintf((char *) fm,"%d\n",numero*2);
	munmap(fm,FILE_LENGTH);
	return EXIT_SUCCESS;
}
