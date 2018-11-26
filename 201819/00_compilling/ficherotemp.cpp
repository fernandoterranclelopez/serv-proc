#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
typedef int temp_file_handle;

temp_file_handle escribir_fichero_temporal(char *buffer, size_t longitud)
{
	char nombre_fichtemp[] = "/tmp/temp_file.XXXXXX";
	int fd = mkstemp(nombre_fichtemp);
	unlink(nombre_fichtemp);
	write(fd,&longitud, sizeof(longitud));
	write(fd,buffer,longitud);
	return fd;
}
char *leer_fichero_temporal(temp_file_handle temp_file, size_t *longitud )
{
	char *buffer = NULL;
	int fd = temp_file;
	lseek(fd,0,SEEK_SET);
	read(fd,longitud,sizeof(*longitud));
	buffer = (char *) malloc(*longitud);
	read(fd,buffer,*longitud);
	close(fd);
	return buffer;
}
int
main(int argc, char *argv[]){
	char *buffer = NULL;
	int fd;
        size_t longitud;
        fd = escribir_fichero_temporal(buffer, longitud);
	buffer = leer_fichero_temporal(fd, &longitud);
	return EXIT_SUCCESS;
}
