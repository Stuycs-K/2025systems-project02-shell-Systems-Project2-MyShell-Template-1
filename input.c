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
#include <error.h>

void handleInput(int argc, char * argv[]) {
  char buffer[255];
  FILE * isUser;
  isUser = fopen("./input", "r");
  if (argc > 1) {
    while (fgets(buffer, 255, stdin)) {
      char * arr[20];
      parse_args(buffer, arr);
    }
  }
  else {
    printf("\n", argv);
  }
}
