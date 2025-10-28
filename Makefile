bin/extreme-autoclicker: main.c
	mkdir -p bin
	gcc -g -Wall -o bin/extreme-autoclicker main.c -lX11

all: bin/extreme-autoclicker

clean:
	rm -rf bin
