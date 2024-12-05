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
    if (i == 0 && strcmp(token, "cd") == 0) {
      return 1;
    }
    arg_ary[i] = token;
    i++;
  }
  arg_ary[i] = NULL;
  return 0;
}

int redirection(int dest, int source){
  int ret = dup(dest);
  dup2(source, dest);
  return ret;
}

int checkLessThan(char** argAry){
  char filename[124];
  int i=0;
  char checkFile='n'; // n or y - Determines whether this iteration has the file to redirect. Char because it takes 1 byte.
  while(argAry[i]!=NULL){
    if(checkFile=='y'){
       strcpy(filename,argAry[i]);
       printf("%s",filename);
      break;
      }
    if(strcmp(argAry[i],"<")==0) checkFile='y';
    i++;
  }
  if (checkFile=='y'){ // CHECK FOR < AND GET NAME
    FILE* file = fopen("filename", "r");
    int backupStdin ;
    backupStdin = redirection(STDIN_FILENO,fileno(file));//redirects stdin to file
    execvp(argAry[0],argAry);
    fflush(stdin);
    wait(NULL);
    dup2(STDIN_FILENO,backupStdin);//stdin is back to user input
  }
  return 0;
}
