#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int
main(int argc, char *argv[]){
        FILE* fp;
        char linea[0x100];
        char longitud;
        fp = popen("ls -l","r");
        fgets(linea,0x100,fp);
        while(!feof(fp)){
                longitud = strlen(linea);
                for(int i = longitud-1; i>0; i++)
                        putchar(linea[i]);
                fgets(linea,0x100,fp);
        }
        pclose(fp);
	return EXIT_SUCCESS;
}
