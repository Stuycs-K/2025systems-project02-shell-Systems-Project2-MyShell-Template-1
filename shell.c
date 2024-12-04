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
  int redirBackup = 1;
  printCWD();
  while (fgets(buffer, 511, stdin)){
    if (strcmp(buffer, "exit\n") == 0) {
      return 0;
    }
    printCWD();
    buffer[strcspn(buffer, "\n")] = 0;
    int len = parse_args(buffer, argAry);
    for (int i = 0; i < len; i ++){
      if (argAry[i][0] == '>'){
        int file = open(argAry[i+1], O_CREAT|O_RDWR|O_APPEND, 0644);
        dup2(file, 1);
        // argAry[i] = NULL;
        // argAry[i+1] = NULL;
      }
    }
    if (redirBackup < 0) err();
    int p = fork();
    if (p == 0) execvp(argAry[0], argAry);
    fflush(stdin);
    dup2(redirBackup, 1);
    wait(&status);
  }
  printf("\n");
  return 0;
}
