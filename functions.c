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

void printCWD(){
  char buf[1024];
  char * bufp = buf;
  char name[500];
  int temp = getlogin_r(name, 499);
  if (temp < 0) err();
  bufp = getcwd(buf, 1023);
  if (bufp == NULL) err();
  bufp = strstr(buf, name);
  bufp = strstr(bufp, "/");
  char tilda[1024];
  strcpy(tilda, "~");
  strcat(tilda, bufp);
  strcat(tilda, "$");
  printf("%s\n", tilda);
}

void parse_args( char * line, char ** arg_ary ) {
  int i = 0;
  char * token;
  while ((token = strsep(& line, " "))) {
    arg_ary[i] = token;
    i++;
  }
  arg_ary[i] = NULL;
}
