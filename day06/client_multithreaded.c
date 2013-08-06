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
#include <pthread.h>
//#include <conio.h>
#include "synch_printf.h"
#include <fcntl.h>

#define MAX_TRY_COUNT 3

static char send_buffer[2][1024];
static char receive_buffer[1024];

static pthread_mutex_t send_buffer_access;
static pthread_cond_t send_buffer_0_cv;
static pthread_cond_t send_buffer_1_cv;
static int sock_fd = 0;

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


int check_connect_status(int s){	
	if (s < 0){
		printf("status %d errno %d\n",s, errno);
		return 1;
	}
	return 0;
}

void *inputThreadRoutine(void *threadid)
{
	int tid = *((int*)(threadid));
	unsigned char c;
	unsigned long index = 0;
	synch_printf("%d ok\n", tid);
	do{
		c = getchar();
		if ((c == 8) && (index>0)){
			index--;
			send_buffer[1][index] = 0;
		}
		send_buffer[1][index] = c;
		if (index<sizeof(send_buffer[1])){
			index++;
		}
		
		if( c == '\n'){
			int len;
			send_buffer[1][index] = 0;
			pthread_mutex_lock(&send_buffer_access);
			len = strlen(send_buffer[1]);
			synch_printf("\nbuffer:\n%s\nsize\n%d\n",send_buffer[1], len);
			memcpy(&(send_buffer[0]), &(send_buffer[1]), len+1);
			memset(&(send_buffer[1]), 0, len);
			pthread_cond_signal(&send_buffer_0_cv);
			printf("Signalled to write. Input thread falling asleep\n");
			pthread_cond_wait(&send_buffer_1_cv, &send_buffer_access);
			pthread_mutex_unlock(&send_buffer_access);
			
			index = 0;
		}
	}while(1);
	pthread_exit(NULL);
}

void *receiveThreadRoutine(void *threadid)
{
	int tid = *((int*)(threadid));
	char receive_buffer[1024];
	int n = 0;
	synch_printf("%d ok\n", tid);
	while (1){
		while ( (receive_buffer[strlen(receive_buffer)-1] != '\n') &&
				((n = read(sock_fd, receive_buffer, sizeof(receive_buffer)-1)) > 0))
		{
			receive_buffer[n] = 0;
			write (1, receive_buffer, strlen(receive_buffer));//1 - stdout
		} 
	}
	if(n < 0)
    {
        printf("\n Read error \n");
    }
	
}

int main(int argc, char *argv[])
{
    int *tid;
	int status;
	int n, last_n, n_sum;
	int n_size;
	int try_count;
	struct sockaddr_in serv_addr; 
	unsigned short server_port = 5000; // default port value;
	pthread_t receive_thread;
	pthread_t input_thread;
	
    if (check_parameters_count(argc)){
		//error
		return 1;
	}

    memset(receive_buffer, 0, sizeof(receive_buffer)); // clear receive buffer
    memset(send_buffer[0], 0, sizeof(send_buffer[0]));
	
	pthread_mutex_init(&send_buffer_access, NULL);
	pthread_cond_init (&send_buffer_0_cv, NULL);
	pthread_cond_init (&send_buffer_1_cv, NULL);
	
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
    if(connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 
	
	init_synch_printing();
	tid = (int *)malloc(sizeof(int));
	if (!tid){
		return 1;
	}
	*tid = 1;
	pthread_create(&input_thread, NULL, inputThreadRoutine,(void *)(tid));
	
	tid = (int *)malloc(sizeof(int));
	if (!tid){
		return 1;
	}
	*tid = 2;
	pthread_create(&receive_thread, NULL, receiveThreadRoutine, (void*)(tid));
	while (1){
		pthread_mutex_lock(&send_buffer_access);
		printf ("main thread falling asleep\n");
		pthread_cond_wait(&send_buffer_0_cv, &send_buffer_access);
		printf ("sending message: \n%s\n", send_buffer[0]);
		n_size = strlen(send_buffer[0]);
		n_sum = 0;
		try_count = 0;
		do{
			n = write (sock_fd, send_buffer[0], n_size-n_sum); 
			printf ("Write returned %d\n", n);
			if (n < 0){
				printf("Socket failed. Attempt to reconnect\n");
				status = connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
				if (check_connect_status(status)){
					return 1;
				}
			}else{
				if (!n){
					try_count++;
				}else{
					if (try_count >= MAX_TRY_COUNT){
						printf("Resend failed %d times. Terminating.\n", MAX_TRY_COUNT);
						return 1;
					}else{
						n_sum+=n;
					}
				}
			}
		}while(n_sum<n_size);
		synch_printf("write complete\n");
		pthread_cond_signal(&send_buffer_1_cv);
		pthread_mutex_unlock(&send_buffer_access);
	}
	
    return 0;
}