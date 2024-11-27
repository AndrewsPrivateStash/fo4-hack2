SHELL := bash
SRCS    := $(wildcard *.c)
CC       := gcc
BIN      := fo4
CFLAGS   := -Wall -Wextra -Werror -ggdb -Og
CFLAGS   += -Wnull-dereference
CFLAGS   += -Wpointer-arith
CFLAGS   += -Wcast-align
CFLAGS   += -Wwrite-strings
CFLAGS   += -Wswitch-default
CFLAGS   += -Wunreachable-code
CFLAGS   += -Winit-self
CFLAGS   += -Wmissing-field-initializers
CFLAGS   += -Wstrict-prototypes
CFLAGS   += -Wundef
CFLAGS   += -Wduplicated-cond
CFLAGS   += -Wfloat-equal
CFLAGS   += -Wshadow

all: $(BIN)

release: CFLAGS=-Wall -O3 -DNDEBUG
release: clean
release: $(BIN)

$(BIN): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@


clean:
	rm -f $(BIN)
