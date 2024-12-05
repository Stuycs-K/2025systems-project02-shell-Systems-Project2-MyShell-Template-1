#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>
#include <sys/wait.h>
#include "functions.h"

int main() {
  char buffer[512];
  char * argAry[512];
  int status;
  printCWD();
  while (fgets(buffer, 511, stdin)){
    if (strcmp(buffer, "exit\n") == 0) {
      exit(0);
    }
    printCWD();
<<<<<<< HEAD
    char * line = (char *) malloc(512);
    strcpy(line, buffer);
    line[strcspn(line, "\n")] = 0;
    char * currCommand;
    while ((currCommand = strsep(& line, ";"))) {
      parse_args(currCommand, argAry);
      int p = fork();
      if (p == 0) execvp(argAry[0], argAry);
      fflush(stdin);
      wait(&status);
    }
    free(line);
=======
    buffer[strcspn(buffer, "\n")] = 0;
    parse_args(buffer, argAry);
    int p = fork();
    if (p == 0) checkLessThan(argAry);
    fflush(stdin);
    wait(&status);
>>>>>>> WahlinK
  }
  printf("\n");
  return 0;
}
