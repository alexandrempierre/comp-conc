#compilador de C
CC := gcc
#diretorio dos arquivos .h
IDIR := include
#bibliotecas carregadas pelo compilador
LDLIBS := -lm
#flags para o compilador
CFLAGS := -W -Wall -I$(IDIR)

#diretorio dos executaveis
BDIR := bin
#executavel final gerado pelo compilador
EXEC := $(BDIR)/main.out

#diretorio das bibliotecas locais
LDIR := lib
#diretorio do codigo-fonte do programa
SDIR := src
#arquivos .c com caminho a partir do diretorio raiz do projeto
CFILES := $(foreach dir, $(LDIR) $(SDIR), $(wildcard $(dir)/*.c))

#diretorio dos arquivos .o
ODIR := bin/obj
#arquivos.o com caminho a partir da raiz do projeto
OBJ:= $(foreach file, $(CFILES), $(patsubst $(dir $(file))%.c, $(ODIR)/%.o, $(file)))


all: mkObjDir $(EXEC) clean
$(EXEC): $(OBJ)
	@$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
# TODO: generalizar essa regra para permitir programas cujo codigo fonte tenha
# 	mais de um arquivo
$(ODIR)/main.o: $(SDIR)/main.c
	@$(CC) -o $@ -c $< $(CFLAGS)
$(ODIR)/%.o: $(LDIR)/%.c
	@$(CC) -o $@ -c $< $(CFLAGS)
mkObjDir:
	@if [ ! -e $(ODIR) ]; then mkdir -p $(ODIR); fi
.PHONY: clean mrproper
clean:
	@rm -rf $(ODIR)
mrproper:
	@if [ -e $(EXEC) ]; then rm $(EXEC); fi
