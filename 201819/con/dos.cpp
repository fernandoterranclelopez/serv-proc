#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#define FILE_LENGTH 0x100
int 
random_range(unsigned const low, unsigned const high){
	unsigned const range = high - low +1;
	return low + (int) (((double)range) * rand() / (RAND_MAX + 1.0));
}
int
main(int argc, char *argv[]){
	int fd;
	void *fm;
	srand(time(NULL));
	fd = open(argv[1],O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	lseek(fd,FILE_LENGTH+1,SEEK_SET);
	write(fd,"",1);
	lseek(fd,0,SEEK_SET);

	fm = mmap(0,FILE_LENGTH,PROT_WRITE,MAP_SHARED,fd,0);
	close(fd);
	sprintf((char *) fm, "%d\n", random_range(0,200));
	munmap(fm,FILE_LENGTH);
	return EXIT_SUCCESS;
}
