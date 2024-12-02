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

void parse_args( char * line, char ** arg_ary ) {
  int i = 0;
  char * token;
  while (token = strsep(& line, " ")) {
    arg_ary[i] = token;
    i++;
  }
  arg_ary[i] = NULL;
}

int main() {
  char line[128] = "echo 8 6 7 5 3 0 9";

  char * arr[15];
  parse_args(line, arr);
  execvp(arr[0], arr);

  return 0;
}
