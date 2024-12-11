compile: shell.o functions.o
	@gcc -o shell shell.o functions.o
shell.o: shell.c functions.h
	@gcc -c -Wall shell.c
functions.o: functions.c
	@gcc -c -Wall functions.c
clean:
	rm -rf *.o shell
