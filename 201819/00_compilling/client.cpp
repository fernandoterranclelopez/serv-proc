#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[]){
	char *server_name = getenv("9999");
	if(server_name = NULL)
    		server_name = "server.my-company.com";
	printf("accesing server %s\n", server_name);
	return EXIT_SUCCESS;
}
