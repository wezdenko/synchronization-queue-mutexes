CC = gcc -g -Wall

all: cc link clean

cc:
	$(CC) -c main.c
	$(CC) -c mutex.c
	$(CC) -c processes.c
	$(CC) -c queue.c

link:
	$(CC) -o main queue.o mutex.o processes.o main.o

clean:
	rm *.o

