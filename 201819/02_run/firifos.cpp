#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int 
spawn(char *program, char **arg_list){
	pid_t proceso_hijo;
	proceso_hijo = fork();
	if(proceso_hijo != 0)
		return proceso_hijo;
	else{
		execvp(program,arg_list);
		fprintf(stderr, "an error occurred in execvp\n");
		abort();
	}
}
int
main(int argc, char *argv[]){
	char *arg_list[] = {
		"firefox",
		"-l",
		"/",
		NULL
	};
	spawn("firefox",arg_list);
	printf("done with main program\n");
	return EXIT_SUCCESS;
}
