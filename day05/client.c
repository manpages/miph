#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 


int check_parameters_count(int argc){
	if(argc != 2)
    {
        printf("\n Usage: cliemt <server address> [<server port>] \n");
        return 1;
    }
	return 0;
}

int setup_server_address_struct(struct sockaddr_in *serv_addr_struct, char *server_address, unsigned short server_port){
	memset(serv_addr_struct, '0', sizeof(*serv_addr_struct)); 

    serv_addr_struct->sin_family = AF_INET;
    serv_addr_struct->sin_port = htons(server_port); 

    if(inet_pton(AF_INET, server_address, &(serv_addr_struct->sin_addr))<=0) // resolve server address
    {
        printf("\n Cannot resolve server address\n");
        return 1;
    }
}	

int main(int argc, char *argv[])
{
    int sock_fd = 0, n = 0;
    char receive_buffer[1024];
	char send_buffer[1024];
    struct sockaddr_in serv_addr; 
	unsigned short server_port = 5000; // default port value;
	
    if (check_parameters_count(argc)){
		//error
		return 1;
	}

    memset(receive_buffer, 0, sizeof(receive_buffer)); // clear receive buffer
    
	if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

	if (argc > 2){ // check if port supplied
		server_port = atoi(argv[2]);
	}
	
	setup_server_address_struct(&serv_addr, argv[1], server_port);
	printf("connecting %s %d\n", argv[1], server_port);
	
	// attempt to connect
    if( connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 
	
	//handling read;
	printf("reading\n");
    while ( (receive_buffer[strlen(receive_buffer)-1] != '\n') &&
			((n = read(sock_fd, receive_buffer, sizeof(receive_buffer)-1)) > 0))
    {
        receive_buffer[n] = 0;
        write (1, receive_buffer, strlen(receive_buffer));//1 - stdout
	} 
	printf("done writing\n");
    if(n < 0)
    {
        printf("\n Read error \n");
    } 
	
	//handling write
	printf("writing\n");
	write (sock_fd, "all good!\n", 10);
	
	printf("closing\n");
	
	close (sock_fd);
	
    return 0;
}