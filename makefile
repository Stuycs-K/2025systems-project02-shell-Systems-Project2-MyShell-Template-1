compile: shell.c
	@gcc shell.c -o shell
clean:
	rm -rf *.o shell
