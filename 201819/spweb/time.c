#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/endfile.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include <string.h>
#include "server.h"

static char *page_start =
"<html>\n"
" <body>\n"
"  <pre>\n";

static char *page_end =
"  </pre>\n"
" </body>\n"
"</html>\n";
//Problema abriendo proc/issue
static char *error_page =
"<html>\n"
" <body>\n"
"  <p>Error: Could not open /proc/issue.</p>\n"
" </body>\n"
"</html>\n";
//HTML source error
static char *error_message = "Error reading /proc/issue.";

void module_generate(){
        int input_fd;
        struct stat file_info;
        int rval;

        //Abrir etc/issue
        input_fd = open("etc/issue", O_RDONLY);
        if(input_fd == -1)
                system_error("open");
        //Obetener informacion del fichero
        rval = fstat(input_fd,&file_info);
        if(rval == -1)
                //No podremos abrir el fichero
                write(fd, error_page, strlen(error_page));
        else{
                int rval;
                off_t offset = 0;
                write(fd,page_start, strlen(page_start));
                //Copiar desde proc/issue al socket
                rval = sendfile(fd,input_fd,&offset,file_info.st_size);
                if(rval == -1)
                        //Hubo error enviadno eso al socket
                        write(fd,error_message,strlen(error_message));
                //Fin de la pagina
                write(fd,page_end,strlen(page_end));
        }
        close(input_fd);
}
