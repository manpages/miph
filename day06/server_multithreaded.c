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
#include <string.h>

#include "synch_printf.h"

#define WORKER_THREAD_NUM 3

static int shared_fd;

static pthread_mutex_t connection_access;
static pthread_cond_t connection_access_cv;
static pthread_cond_t dispatch_cv;

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

int check_match(char *s,char *ss){
	int i = 0;
	while(ss[i] != '\0'){
		if(s[i] != ss[i]){
			return 0;
		}
		i++;
	}
	return 1;	
}

int rfind(char *s, char *ss, int end_index){
	int ss_length = strlen(ss);
	if (!ss_length){
		return end_index;
	}
	int search_index;
	if (end_index < 0){
		end_index = strlen(s)-1;
	}
	search_index = end_index-ss_length+1;
	if (search_index<0){
		return -1;
	}
	
	while (search_index>=0){
		char *p = (char *)(s+search_index);
		int match = check_match(p, ss);
		if( match){
			return search_index;
		}
		search_index--;
	}
	return search_index;
}

void *workerThreadRoutine(void *threadid)
{
	int tid = *((int*)(threadid));
	unsigned char c;
	char receive_buffer[1025];
	char send_buffer[1025];
	int n;
	unsigned long index = 0;
	int conn_fd;
	
	synch_printf("thread %d created\n", tid);
	
	memset(receive_buffer, 0, sizeof(receive_buffer));
	memset(send_buffer, 0, sizeof(send_buffer));
	
	while (1){
		int ready_to_send = 1;
	
		pthread_mutex_lock(&connection_access);
		pthread_cond_wait(&connection_access_cv, &connection_access);
		conn_fd = shared_fd;
		shared_fd = 0;
		pthread_cond_signal(&dispatch_cv);
		pthread_mutex_unlock(&connection_access);
	
		do{
			if (ready_to_send){
				snprintf(send_buffer, sizeof(send_buffer), "Server waiting messages\n");
				write(conn_fd, send_buffer, strlen(send_buffer));
				ready_to_send = 0;
			}
			n = read(conn_fd, receive_buffer, sizeof(receive_buffer));
			if (n){
				write(1, receive_buffer, n);//stdout
				if (rfind(receive_buffer,"\n",n)){
					ready_to_send = 1;
				}
			}
		}while(n);
		
		close(conn_fd);
	}
	
}

int main(int argc, char *argv[])
{
    int socket_fd = 0, conn_fd = 0;
	int i;
	int *tid;
	pthread_t worker_threads[WORKER_THREAD_NUM];
    

    socket_fd = open_server_socket(5000);
	printf("socket opened\n");
	
	listen(socket_fd, 10); 
	printf("listening\n");
    
	pthread_mutex_init(&connection_access, NULL);
	pthread_cond_init (&connection_access_cv, NULL);
	pthread_cond_init (&dispatch_cv, NULL);
	
	conn_fd = 0;
	
	i = 0;
	while(i < WORKER_THREAD_NUM){
		tid = (int *)malloc(sizeof(int));
		if (!tid){
			return 1;
		}
		*tid = i;
		pthread_create(&worker_threads, NULL, workerThreadRoutine, (void*)(tid));
		i++;
	}
	
	synch_printf("Init complete! =)\n");
	while(1)
    {
        synch_printf("accepting connection\n");
		conn_fd = accept(socket_fd, (struct sockaddr*)NULL, NULL); 
		
		pthread_mutex_lock(&connection_access);
		shared_fd = conn_fd;
		pthread_cond_signal(&connection_access_cv);
		pthread_cond_wait(&dispatch_cv, &connection_access);
		pthread_mutex_unlock(&connection_access);
		synch_printf("connection dispatched\n");
    }
}