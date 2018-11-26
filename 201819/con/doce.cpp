#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int
main(int argc, char *argv[]){
        int pid;
        int numero[] ={9,12,12,44,55,66,77};
        int nuevo[7];
        pid = fork();
        if(pid == 0){
                FILE *fic = fopen("numero.txt","w");
                fwrite(numero,sizeof(int),7,fic);
                fclose(fic);
        }else{
                FILE *fic = fopen("numero.txt","r");
                fread(nuevo,sizeof(int),sizeof(nuevo),fic);
                for(int i=0; i<7; i++)
                        printf("The number %i\n",nuevo[i]);
                fclose(fic);
                waitpid(pid,NULL,0);
        }
	return EXIT_SUCCESS;
}
