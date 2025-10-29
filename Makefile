bin/extreme-autoclicker: main.c
	mkdir -p bin
	gcc -g -Wall -o bin/extreme-autoclicker main.c $(shell pkg-config --cflags --libs libevdev gtk4)

all: bin/extreme-autoclicker

clean:
	rm -rf bin
