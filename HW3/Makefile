CC = cc
CFLAGS = -std=c99 -pedantic -Wall
OBJECTS = output.o

# output.out: 

output.o: main.c kmeans.h kmeans.c
	gcc main.c kmeans.c -o output.out
	./output.out test.txt 3