#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 


int open_server_socket(unsigned short port){
	
	struct sockaddr_in serv_addr; 
	int fd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port); 

    bind(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
	return fd;
}

int main(int argc, char *argv[])
{
    int socket_fd = 0, conn_fd = 0;
    int n, last;
	
    char send_buffer[1025];
	char receive_buffer[1025];
	
	memset(receive_buffer, 0, sizeof(receive_buffer));
	memset(send_buffer, 0, sizeof(send_buffer));
	

    socket_fd = open_server_socket(5000);
	printf("socket opened\n");
	
	listen(socket_fd, 10); 
	printf("listening\n");
    
	while(1)
    {
        printf("accepting connection\n");
		conn_fd = accept(socket_fd, (struct sockaddr*)NULL, NULL); 
		
		printf("writing\n");
		snprintf(send_buffer, sizeof(send_buffer), "server says hello world!\n");
        write(conn_fd, send_buffer, strlen(send_buffer)); 
		
		printf("reading\n");
		
		do{
			n = read(conn_fd, receive_buffer, sizeof(receive_buffer));
			if (n >= 0){
				if (n){
					write(1, receive_buffer, n);//stdout
					last = n-1;
				}
			}else{
				printf("socket error\n");
			}
		}while(receive_buffer[last] != '\n');
		
		
		printf("closing connection\n");
		close(conn_fd);
        sleep(1);
     }
}