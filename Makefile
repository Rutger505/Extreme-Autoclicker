bin/extreme-autoclicker:
	mkdir -p bin
	gcc \
		$(shell pkg-config --cflags gtk4 libevdev) \
		-g \
		-Wall \
		-o bin/extreme-autoclicker \
		src/main.c \
		src/pointer.c \
		$(shell pkg-config --libs gtk4 libevdev)

all: bin/extreme-autoclicker

clean:
	rm -rf bin
all: bin/extreme-autoclicker

clean:
	rm -rf bin
