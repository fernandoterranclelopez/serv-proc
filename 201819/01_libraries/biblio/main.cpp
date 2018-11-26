#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mates.h"

int
main(int argc, char *argv[]){
	printf("2 y 2 son %.2lf y 4 y 2 son %.2lf\n", suma(2,2), suma(4,2));
	return EXIT_SUCCESS;
}
