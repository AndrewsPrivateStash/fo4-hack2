SHELL := bash
SRCS    := $(wildcard *.c)
CC       := gcc
BIN      := fo4
CFLAGS   := -Wall -Og

all: $(BIN)

release: CFLAGS=-Wall -O3 -DNDEBUG
release: clean
release: $(BIN)

$(BIN): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@


clean:
	rm -f $(BIN)