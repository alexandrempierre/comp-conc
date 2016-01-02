CC=gcc

IDIR=include
LDLIBS=-lm
CFLAGS=-W -Wall -I$(IDIR)

BDIR:=bin
EXEC=$(BDIR)/main.out

LDIR=lib
SDIR=src
CFILES=$(foreach dir, $(LDIR) $(SDIR), $(wildcard $(dir)/*.c))
OBJ=$(CFILES:.c=.o)

all: $(EXEC) clean
$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
.PHONY: clean mrproper
clean:
	rm -rf *.o */*.o
mrproper:
	if [ -e $(EXEC) ]; then rm $(EXEC); fi
