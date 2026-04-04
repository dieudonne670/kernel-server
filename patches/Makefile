CC = gcc
CFLAGS = -fPIC -shared -Wall

all: example_patch.so

example_patch.so: example_patch.c
	$(CC) $(CFLAGS) example_patch.c -o example_patch.so

clean:
	rm -f example_patch.so
