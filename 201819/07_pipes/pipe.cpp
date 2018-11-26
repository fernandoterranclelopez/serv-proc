#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define N 2
#define TOT 1024
void 
writer(const char *message, int count, FILE* stream){
	for(;count > 0; --count){
		fprintf(stream,"%s\n",message);
		fflush(stream);
		usleep(1000);
	}
}

void 
reader(FILE* stream){
	char  buffer[TOT];
	while(!feof(stream) && !ferror(stream) && fgets(buffer,sizeof(buffer),stream)!= NULL)
		fputs(buffer,stdout);
}

int	
main(int argc, char *argv[]){
	int fds[N];
	pid_t pid;
	pipe(fds);
	pid = fork();
	if(pid == (pid_t)0){
		FILE* stream;
		close(fds[1]);
		stream = fdopen(fds[0],"r");
		reader(stream);
		close(fds[0]);
	}
	else{
		FILE* stream;
		close(fds[0]);
		stream = fdopen(fds[1],"w");
		writer("Ich bin so schön verstrahlt.",5000,stream);
		close(fds[1]);
	}
	return EXIT_SUCCESS;
}
