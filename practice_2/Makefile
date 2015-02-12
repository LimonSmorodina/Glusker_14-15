CC=mingw32-g++
CFLAGS=-Wall -Wextra -Wpedantic -O2

all: pr2.exe

pr2.exe: main.o commandInterface.o data.o
	$(CC) $(CFLAGS) main.o commandInterface.o data.o -o pr2.exe

main.o:
	$(CC) $(CFLAGS) -c main.cpp

commandInterface.o:
	$(CC) $(CFLAGS) -c commandInterface.cpp

data.o:
	$(CC) $(CFLAGS) -c data.cpp

clean:
	rm -rf *.o