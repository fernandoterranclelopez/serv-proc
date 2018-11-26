#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#define FILE_LENGTH 0x100
int
main(int argc, char *argv[]){
	const char *borde [] = {
	"**********\n"
	"*        *\n"
	"*        *\n"	
	"*        *\n"	
	"*        *\n"	
	"*        *\n"	
	"*        *\n"
	"**********\n"
	};

	int fd;
	void *fm;

	fd = open(argv[1],O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	lseek(fd,FILE_LENGTH+1,SEEK_SET);
	write(fd," ",1);
	lseek(fd,0,SEEK_SET);

	fm = mmap(0,FILE_LENGTH,PROT_WRITE,MAP_SHARED,fd,0);
	close(fd);
	sprintf((char *) fm, "%s\n",*borde);
        munmap(fm,FILE_LENGTH);
	return EXIT_SUCCESS;
}
