CC = gcc
CFLAGS = -Wall -Wextra -O3 -I./sha256
TARGET = rbgen

SRCS = main.c sha256/basic_hashing.c
OBJS = main.o sha256/basic_hashing.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c sha256/basic_hashing.h
	$(CC) $(CFLAGS) -c main.c -o main.o

sha256/basic_hashing.o: sha256/basic_hashing.c sha256/basic_hashing.h
	$(CC) $(CFLAGS) -c sha256/basic_hashing.c -o sha256/basic_hashing.o

clean:
	rm -f *.o sha256/*.o $(TARGET)

# installs to hidden folder in home dir
install: $(TARGET)
	mkdir -p $(HOME)/.local/bin
	cp $(TARGET) $(HOME)/.local/bin/
	@echo "Successfully installed to $(HOME)/.local/bin"
	@echo "Run 'export PATH=\$$PATH:\$$HOME/.local/bin' to use it anywhere."