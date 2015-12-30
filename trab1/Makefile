all: main clean
main: main.o integral.o funcoes.o arv.o
	gcc -o main main.o integral.o funcoes.o arv.o -lm -W -Wall
main.o: main.c integral.h funcoes.h
	gcc -o main.o -c main.c -W -Wall
integral.o: integral.c funcoes.h arv.h
	gcc -o integral.o -c integral.c -W -Wall
funcoes.o: funcoes.c
	gcc -o funcoes.o -c funcoes.c -W -Wall
arv.o: arv.c
	gcc -o arv.o -c arv.c -W -Wall
clean:
	rm -rf *.o
mproper:
	rm main
