all: server client

test: test.o
	gcc test.o -o test

test.o: test.c
	gcc -c test.c

server: server.o
	gcc server.o -lstdc++ -o server

server.o: server.c
	gcc -c server.c

client: client.o
	gcc client.o -lstdc++ -o client

client.o: client.c
	gcc -c client.c

client_multithreaded: client_multithreaded.o synch_printf.o
	gcc client_multithreaded.o synch_printf.o -pthread -lstdc++ -o client_multithreaded

client_multithreaded.o: client_multithreaded.c
	gcc -c client_multithreaded.c
	
server_multithreaded: server_multithreaded.o
	gcc server_multithreaded.o synch_printf.o -pthread -lstdc++ -o server_multithreaded

server_multithreaded.o: server_multithreaded.c
	gcc -c server_multithreaded.c

extendable_string.o: extendable_string.c extendable_string.h
	gcc -c extendable_string.c
	
extendable_string_test: extendable_string_test.c extendable_string.o
	gcc -c extendable_string_test.c
	gcc extendable_string_test.o extendable_string.o -lstdc++ -o extendable_string_test

experiment: experiment.c
	gcc -c experiment.c
	gcc experiment.o extendable_string.o -lstdc++ -o experiment

str_test: extendable_string.o extendable_string_test 

synch_printf.o: synch_printf.c synch_printf.h
	gcc -c synch_printf.c

clean:
	rm -rf *.o