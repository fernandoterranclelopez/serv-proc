#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[]){
	
	FILE *hilo = popen("ssh oscar2710@localhost","w");
        
	fprintf(hilo,"Uyy");
	fprintf(hilo,"Ups");

	pclose(hilo);
	return EXIT_SUCCESS;
}
