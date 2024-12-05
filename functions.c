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
  printf("\033[34m");
  printf("\033[1m");
  printf("%s", tilda);
  printf("\33[0m");
  printf("$ ");
}

int parse_args( char * line, char ** arg_ary ) {
  int i = 0;
  char * token;
  while ((token = strsep(& line, " "))) {
    arg_ary[i] = token;
    i++;
  }
  arg_ary[i] = NULL;
  return i;
}

int redirection(int source, int dest){
  int ret = dup(dest);
  dup2(source, dest);
  return ret;
}

int run(char** argAry){
  int i=0;
  char checkFile='n'; // n or y - Determines whether this iteration has the file to redirect. Char because it takes 1 byte.
  while(argAry[i]!=NULL){
    if(argAry[i][0]=='<'){
      argAry[i]=NULL;
      checkFile='y';
     break;
    }
    i++;
  }
  if (checkFile=='y'){ // CHECK FOR < AND GET NAME
    int file = open(argAry[i+1], O_RDONLY);

    int backupStdin;
    backupStdin = redirection(file,0);//redirects stdin to file

    redirection(file,0);//redirects stdin to file

  }
  execvp(argAry[0],argAry);
  fflush(stdin);
  return 0;
}
