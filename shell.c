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
  // char line[128] = "echo 8 6 7 5 3 0 9";
  // char * arr[15];
  // parse_args(line, arr);
  // execvp(arr[0], arr);
  printCWD();
  return 0;
}
