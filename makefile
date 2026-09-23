CC = g++
CFLAGS = -std=c++11

all: a.out

a.out: main.cpp
	$(CC) $(CFLAGS) main.cpp -o a.out

clean:
	rm -f a.out
