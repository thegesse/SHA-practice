CC = gcc
CFLAGS = -Wall -Wextra -O3
TARGET = rbgen

all: $(TARGET)

$(TARGET): main.o basic-hashing.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o basic-hashing.o

main.o: main.c basic-hashing.h
	$(CC) $(CFLAGS) -c main.c

basic-hashing.o: basic-hashing.c basic-hashing.h
	$(CC) $(CFLAGS) -c basic-hashing.c

clean:
	rm -f *.o $(TARGET)

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

uninstall:
	rm -f /usr/local/bin/$(TARGET)