bin/extreme-autoclicker: main.c
	mkdir -p bin
	gcc $(shell pkg-config --cflags gtk4 )\
		-g \
		-Wall \
		-o bin/extreme-autoclicker \
		main.c \
		$(shell pkg-config --libs libevdev gtk4)

all: bin/extreme-autoclicker

clean:
	rm -rf bin
