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

<<<<<<< HEAD
int main(int argc, char * argv[]) {
  // char line[128] = "echo 8 6 7 5 3 0 9";
  // char * arr[15];
  // parse_args(line, arr);
  // execvp(arr[0], arr);
  handleInput(argc, argv);
=======
int main() {
  char buffer[512];
  char * argAry[512];
  int status;
>>>>>>> e03cd6efc116d60e0842926c3d12180cca885ee7
  printCWD();
  while (fgets(buffer, 511, stdin)){
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
