CC=gcc
CFLAGS=-I.
LDFLAGS=-lpthread
OBJ=$(patsubst %.c, %.o, $(filter-out %.old.c, $(wildcard *.c)))

EXEC=main.out

all: $(EXEC) clean
$(EXEC): $(OBJ)
	@$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)
.PHONY: clean mrproper
clean:
	@rm -rf *.o
mrproper:
	@rm $(EXEC)
