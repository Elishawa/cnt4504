client: client.o
	gcc client.o -o client

server: server.o
	gcc server.o -o server

showip: showip.o
	gcc showip.o -o showip

showip.o:
	gcc -c showip.c

client.o: client.c 
	gcc -c client.c

server.o: server.c
	gcc -c server.c

clean:
	rm *.o client server
