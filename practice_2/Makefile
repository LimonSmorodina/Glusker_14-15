CC=g++
CFLAGS=-Wall -Wextra -Wpedantic -O2 -std=c++11 -lboost_serialization

all: pr2

pr2: main.o commandInterface.o data.o
	$(CC) $(CFLAGS) main.o commandInterface.o data.o -o pr2

main.o:
	$(CC) $(CFLAGS) -c main.cpp

commandInterface.o:
	$(CC) $(CFLAGS) -c commandInterface.cpp

data.o:
	$(CC) $(CFLAGS) -c data.cpp

clean:
	rm -rf *.o
