#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/wait.h>
int printErr();
int main(int argc, char *argv[]);
char ** prompt();
void piper(char* command1, char* command2);

#endif
