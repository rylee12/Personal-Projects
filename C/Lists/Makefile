# Ryan K Lee
# Title: Makefile
# Description: Makefile for the List ADT

ListClient: ListClient.o List.o
	gcc -o ListClient ListClient.o List.o

ListClient.o: List.h ListClient.c 
	gcc -c -std=c99 -Wall ListClient.c 

List.o: List.h List.c 
	gcc -c -std=c99 -Wall List.c

clean:
	rm -f ListClient ListClient.o List.o

check:
	valgrind --leak-check=full ListClient