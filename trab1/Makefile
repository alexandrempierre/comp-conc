CC=gcc
CFLAGS=-W -Wall -I.
EXEC=main.out
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all: $(EXEC) clean
$(EXEC): $(OBJ)
	@$(CC) -o $@ $^ -lm $(CFLAGS)
%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)
.PHONY: clean mrproper
clean:
	@rm -rf *.o
mrproper:
	@if [ -e $(EXEC) ]; then rm $(EXEC); fi
