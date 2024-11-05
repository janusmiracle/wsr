CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -Wformat-security -Werror

SRC = src/main.c
TARGET = a

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

update: clean all
