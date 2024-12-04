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
      return 0;
    }
    printCWD();
    buffer[strcspn(buffer, "\n")] = 0;
    parse_args(buffer, argAry);
    int p = fork();
    if (p == 0) execvp(argAry[0], argAry);
    fflush(stdin);
    wait(&status);
  }
  printf("\n");
  return 0;
}
