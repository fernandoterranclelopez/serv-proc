#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef NDEBUG
#define DEBUG(x) fprintf(stderr, "DBG(Line: %i): %s\n", __LINE__, (x));
#else
#define DEBUG(x)
#endif

int
main(int argc, char *argv[]){
        DEBUG("Iniciando programa.");
	return EXIT_SUCCESS;
}
