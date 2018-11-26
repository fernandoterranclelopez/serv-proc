#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[]){
        FILE* fd;

        fd = popen("sort","w");
        fprintf(fd,"hola\n");
        fprintf(fd,"adios\n");
        fflush(stdout);
        pclose(fd);
	return EXIT_SUCCESS;
}
