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

void err(){//Prints the error and its error number using errno, then exits the process.
  printf("error number %d\n", errno);
  printf("%s\n", strerror(errno));
  exit(1);
}

void printCWD(){//Prints the command line based on the current directory.
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

int parse_args( char * line, char ** arg_ary ) {//Takes a line and string array. Separates the line into words to be appended to the string array, then appends a null pointer, returning its index.
  int i = 0;
  char * token;
  while ((token = strsep(& line, " "))) {
    arg_ary[i] = token;
    i++;
  }
  arg_ary[i] = NULL;
  return i;
}

int redirection(int source, int dest){//Redirects dest from source, Can take ints like stdin/out and file pointers. Returns dest's initial file descriptor.
  int ret = dup(dest);
  dup2(source, dest);
  return ret;
}

int run(char** argAry, int len){//Takes a string list and its length. Identifies and responds to < > and | redirectors by redirecting certain file descriptors, and then executes the line as it would execute in bash.
  int i = 0;
  int pipeLoc = 0;
  int inputLoc = 0;
  int outputLoc = 0; //Determines whether this iteration has the file to redirect. Char because it takes 1 byte.
  while(i < len){
    if(argAry[i][0] == '<'){
      argAry[i] = NULL;
      inputLoc = i;
    }
    else if (argAry[i][0] == '>'){
      argAry[i] = NULL;
      outputLoc = i;
    }
    else if (argAry[i][0] == '|'){
      argAry[i] = NULL;
      pipeLoc = i;
    }
    i++;
  }
  if (pipeLoc > 0){
    int status;
    int backup = 1;
    int temp = open("tempmpmp.txt", O_CREAT|O_RDWR|O_TRUNC, 0644);
    if (inputLoc > 0){ // CHECK FOR < AND GET NAME
      int fileREAD = open(argAry[inputLoc + 1], O_RDONLY);
      if (fileREAD < 0) err();
      redirection(fileREAD,0);//redirects stdin to file
    }
    int q = fork();
    if (q != 0) wait(&status);
    if (q == 0) {
      backup = redirection(temp,1);
      execvp(argAry[0],argAry);
    }
    redirection(backup, 1);
    if (outputLoc > 0){ // CHECK FOR < AND GET NAME
      int fileWRITE = open(argAry[outputLoc + 1], O_CREAT|O_RDWR|O_APPEND, 0644);
      if (fileWRITE < 0) err();
      redirection(fileWRITE, 1);//redirects file to stdout
    }
    temp = open("tempmpmp.txt", O_RDONLY);
    redirection(temp,0);//redirects stdin to file
    char ** tempAry = &argAry[pipeLoc + 1];
    int p = fork();
    if (p != 0) wait(&status);
    if (p == 0){
      execvp(argAry[pipeLoc + 1],tempAry);
    }
    remove("tempmpmp.txt");
    fflush(NULL);
    exit(0);
  }

  if (inputLoc > 0){ // CHECK FOR < AND GET NAME
    int fileREAD = open(argAry[inputLoc + 1], O_RDONLY);
    if (fileREAD < 0) err();
    redirection(fileREAD,0);//redirects stdin to file
  }

  if (outputLoc > 0){ // CHECK FOR < AND GET NAME
    int fileWRITE = open(argAry[outputLoc + 1], O_CREAT|O_RDWR|O_APPEND, 0644);
    if (fileWRITE < 0) err();
    redirection(fileWRITE, 1);//redirects file to stdout
  }
  execvp(argAry[0],argAry);
  fflush(NULL);
  return 0;
}
