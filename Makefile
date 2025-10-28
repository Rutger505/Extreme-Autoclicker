# Compile main.c to bin/main.o
bin/main.o: main.c
	mkdir -p bin
	gcc -g -Wall -c main.c -o bin/main.o

# Link bin/main.o to create bin/Extreme_Autoclicker
bin/Extreme_Autoclicker: bin/main.o
	gcc -g -Wall -o bin/Extreme_Autoclicker bin/main.o -lX11

# Default target
all: bin/Extreme_Autoclicker

# Clean up
clean:
	rm -rf bin
