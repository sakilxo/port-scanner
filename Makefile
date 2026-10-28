CC = clang
CFLAGS = -Wall -Wextra -Wedantic -std=c11 -02

TARGET = portscan
SRC = src/portscan.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(FLAGS) -o $@ $^

clean: 
	rm -f $(TARGET)