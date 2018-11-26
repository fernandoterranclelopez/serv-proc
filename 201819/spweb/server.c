#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include "server.h"

//HTTP encabezado y respuesta para una respuesta exitosa

static char *ok_response = 
"HTTP/1.0 200 OK\n"
"Content-type: text/html\n"
"\n";

// Si hay fallo se carga esto
static char *bad_request_response = 
"HTTP/1.0 400 Bad Request\n"
"Content-type: text/html\n"
"\n"
"<html>\n"
" <body>\n"
"  <h1>Bad Request</h1>\n"
"  <p>This server did not understand your request.</p>\n"
" </body>\n"
"</html>\n";

//Respuesta si el documento no es encontrado
static char *not_found_response_template =
"HTTP/1.0 404 Not Found\n"
"Content-type: text/html\n"
"\n"
"<html>\n"
" <body>\n"
"  <h1>Not Found</h1>\n"
"  <p>The requested URL %s was not found on this server.</p>\n"
" </body>\n"
"</html>\n";

//Respuesta si hay un metodo no entendido
static char *bad_method_response_template = 
"HTTP/1.0 502 Method Not Implemented\n"
"Content-type: text/html\n"
"\n"
"<html>\n"
" <body>\n"
"  <h1>Method Not Implemented</h1>\n"
"  <p>The method %s is not implemented by this server.</p>\n"
" </body>\n"
"</html>\n";

//Gestor para la SIGCHLD para limpiar el proceso que ha terminado
static void clean_up_child_processes(int signal_number){
	int status;
	wait(&status);
}

//Procesar un http GET request para pagina y enviar los resultados a un descriptor de ficheros
static void handle_get(int connection_fd,const char *page){
	struct server_module *module = NULL;
	//Hacer seguro que la pagina empiece con barra oblicuas y no tenga de mas no coje subdirectorios
	if( *page == '/' && strchr(page+1,'/') == NULL){
		char module_file_name[64];
		//La pagina es OK Construir el modulo añadiendo .so al nombre de la pagina
		snprintf(module_file_name,sizeof(module_file_name),"%s.so",page+1);
		module = module_open(module_file_name);
	}
	if(module == NULL){
		//Si no hay ninguno se envia un mensaje de que no se encuentra el modulo
		char response[1024];
		snprintf(response,sizeof(response), not_found_response_template, page);
		write(connection_fd,response,strlen(response));
	}else{
		//Si es Ok se carga se genera y se cierra
		write(connection_fd, ok_response, strlen(ok_response));
		(*module->generate_function)(connection_fd);
		module_close(module);
	}
}
//Gestionar una conexion con el cliente con el file descriptor
static void handle_connection(int connection_fd){
	char buffer[0x100];
	ssize_t bytes_read;
	//Leer datos sobre el cliente
	bytes_read = read(connection_fd,buffer,sizeof(buffer)-1);
	if(bytes_read>0){
		char method[sizeof(buffer)];
		char url[sizeof(buffer)];
		char protocol[sizeof(buffer)];
		//Datos fueron leidos exitosamente  y ponemos \0 al final del buffer
		buffer[bytes_read] = '\0';
		/*La primera linea el cliente envian la peticion HTTP la cual esta compuesta de metodo
		  , la pagina requerida y la version del protocolo*/
		sscanf(buffer,"%s %s %s",method,url,protocol);
		/*El cliente envia varios encabezados siguiendo la peticion*/
		while(strstr(buffer, "\r\n\r\n") == NULL)
			bytes_read = read(connection_fd,buffer,sizeof(buffer));
		//Hacer seguro que lo ultimo leido no fallo. Y si lo hizo hay un problema con la conexion se cierra el fd
		if(bytes_read == -1){
			close(connection_fd);
			return;
		}
		//Checkear el campo del protocolo
		if(strcmp(protocol,"HTTP/1.0") && strcmp(protocol,"HTTP/1.1")){
			//Si no entiende el protocolo se reporta una mala respuesta
			write(connection_fd,bad_request_response,sizeof(bad_request_response));
		}
		else if(strcmp(method,"GET")){
			//Solo implementa el get method
			char response[1024];
			snprintf(response,sizeof(response),bad_method_response_template,method);
			write(connection_fd,response,strlen(response));
		}else
			//respuesta valida
			handle_get(connection_fd,url);
	}
	else if(bytes_read==0)
		//cliente cierra  la conexion
		;
	else
		system_error("read");
}
void server_run(struct in_addr local_address, uint16_t port){
	struct sockaddr_in socket_address;
	int rval;
	struct sigaction sigchld_action;
	int server_socket;

	//Instalar un gestor para SIGCHLD qur limpia el proceso hijo si acaba
	memset(&sigchld_action,0,sizeof(sigchld_action));
	sigchld_action.sa_handler = &clean_up_child_process;
	sigaction(SIGCHLD,&sigchld_action,NULL);
	//Crear un TCP socket
	server_socket = socket(PF_INET, SOCK_STREAM);
	//Construir la estructura del socket
	memset(&socket_address,0,sizeof(socket_address));
	socket_address.sin_family = AF_INET;
	socket_address.sin_port = port;
	socket_address.sin_addr = local_address;
	//Dar la direccion al socket
	rval = bind(server_socket,&socket_address,sizeof(socket_address));
	if(rval!=0)
		system_error("bind");
	//Hacer que el soocket escuche conexiones
	rval = listen(server_socket,10);
	if(rval !=0)
		system_error("listen");
	if(verbose){
		socklen_t address_length;
		address_length = sizeof(socket_address);
		rval = getsockname(server_socket, &socket_address, &address_length);
		assert(rval == 0)
			printf("server listening on %s:%d\n", inet_ntoa(socket_address.sin_addr), (int) ntohs(socket_address.sin_port));
	}
	//Loop infinito gestionando conexiones
	while(1){
		struct sockaddr_in remote_address;
		socklen_t address_length;
		int connection;
		pid_t pid;
		//Aceptar la conexion. Se bloquea hasta que la conexion esta lista
		address_length = sizeof(remote_address);
		connection = accept(server_socket,&remote_address, &address_length);
		if(connection == -1){
			//La llamada a accept fallo
			if(errno = EINTR)
				//Llamada interrumpida por una señal
				continue;
			else
				//Algo fue mal
				system_error("accept");
		}
		if(verbose){
			socklen_t address_length;
			address_length = sizeof(socket_address);
			rval = getpeername(connection, &socket_address, &address_length);
			assert(rval==0)
				printf("Connection accepted from %s\n", inet_ntoa(socket_address.sin_addr));
		}
		pid = fork();
		//creamos dos procesos
		if(pid == 0){
			//cerramos stdin stdout
			close(STDIN_FILENO);
			close(STDOUT_FILENO);

			//No hace nada con el socket que escucha
			close(server_socket);
			//Gestionamos la conexion 
			handle_connection(connection);
			close(connection);
			exit(0);
		}else
			if(pid > 0){
				//Cerramos la conexion
				close(connection);
			}else
				//No se llamo bien a fork
				system_error("fork");
	}

}
