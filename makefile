run:
	@./shell
compile shell: parse.o main.o misc.o
	@gcc -o shell parse.o main.o misc.o
parse.o: parse.c parse.h
	@gcc -c parse.c
main.o: main.c parse.h misc.h
	@gcc -c main.c
misc.o: misc.c misc.h
	@gcc -c misc.c
clean:
	rm *.o
	rm shell
