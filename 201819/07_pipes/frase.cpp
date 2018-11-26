#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int
main(int argc, char *argv[]){
	char input;
	while((input = (char) getchar())!=EOF)
		printf("Key: %c\n",input);
	return EXIT_SUCCESS;
}
