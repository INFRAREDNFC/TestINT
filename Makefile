CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -O2
TARGET=sort
SRC=sort.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
