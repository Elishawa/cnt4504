client: client.o
	gcc client.o -o client

server: server.o
	gcc server.o -o server

client.o: client.c 
	gcc -c client.c

server.o: server.c
	gcc -c server.c

clear:
	rm *.o client server
