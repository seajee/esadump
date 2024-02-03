CC=gcc
CFLAGS=-Wall -Wextra

esadump: main.c
	$(CC) $(CFLAGS) -o esadump main.c

clean:
	rm -rf esadump
