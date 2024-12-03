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

void err(){
  printf("error number %d\n", errno);
  printf("%s\n", strerror(errno));
  exit(1);
}

void parse_args( char * line, char ** arg_ary ) {
  int i = 0;
  char * token;
  while (token = strsep(& line, " ")) {
    arg_ary[i] = token;
    i++;
  }
  arg_ary[i] = NULL;
}

void printCWD(){
  char buf[1024];
  char * bufp = buf;
  char name[500];
  int temp = getlogin_r(name, 499);
  if (temp < 0) err();
  getcwd(buf, 1023);
  bufp = strstr(buf, name);
  printf("%s\n", bufp);
}

int main(int argc, char * argv[]) {
  // char line[128] = "echo 8 6 7 5 3 0 9";
  // char * arr[15];
  // parse_args(line, arr);
  // execvp(arr[0], arr);
  handleInput(argc, argv);
  printCWD();
  return 0;
}
