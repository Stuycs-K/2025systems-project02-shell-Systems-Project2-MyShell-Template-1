#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "execute.h"

void stdoutRedirExec(char* path, char* args[]){
  remove(path);
  int fd1 = open(path, O_WRONLY | O_APPEND | O_CREAT, 0600);
  dup(1);
  dup2(fd1, 1);
  int exec;
  close(fd1);
  exec = execvp(args[0], args);
  if (exec<0){
    perror("stoutRedirect fail");
    exit(1);
  }
}

void stdinRedirExec(char* path, char* args[]){
  int fd1 = open(path, O_RDONLY);
  dup(0);
  dup2(fd1, 0);
  int exec;
  close(fd1);
  exec = execvp(args[0], args);
  if (exec<0){
    perror("stdinRedirect fail");
    exit(1);
  }
}

int PipeRedirExec(char* args[], int pipeLocation, int argsLen){
  pid_t bb;
  bb = fork();
  if(bb < 0){
      perror("fork fail");
      exit(1);
  }
  if(bb == 0){
    remove("temp.txt");
    int fd1 = open("temp.txt", O_WRONLY | O_APPEND | O_CREAT, 0600);
    dup(1);
    dup2(fd1, 1);
    int exec;
    close(fd1);

    char* args1input[100];

    char * arg1 = malloc(sizeof(args));
    strcpy(arg1, args[0]);
    for(int i = 1; i < pipeLocation; i++){
      strcat(arg1, " ");
      strcat(arg1, args[i]);
    }

    int len = parse_args(arg1, args1input);
    if(len > 1 && strcmp(args1input[1],"<") == 0){
      char* newarg1input[100];
      for(int i = 0; i < len-2; i++){
        newarg1input[i] = args1input[i];
      }
      stdinRedirExec(args1input[len - 1], newarg1input);
    }else{
      exec = execvp(args1input[0], args1input);
      if (exec<0){
        perror("stoutRedirect fail: error A");
        exit(1);
      }
    }
    return 0;
  }
  else{
      wait(NULL);

      int fd1 = open("temp.txt", O_RDONLY);
      dup(0);
      dup2(fd1, 0);
      int exec;
      close(fd1);

      char* args2input[100];

      char * arg2 = malloc(sizeof(args));
      strcpy(arg2, args[pipeLocation+1]);
      int foundredir = 1;
      for(int i = pipeLocation + 2; i < argsLen; i++){
          if(strcmp(args[i], ">") == 0){
            foundredir = 0;
            break;
          }
          strcat(arg2, " ");
          strcat(arg2, args[i]);
      }

      int len = parse_args(arg2, args2input);
      remove("temp.txt");

      if(foundredir == 0){
        remove(args[len+2+pipeLocation]);
        int f = open(args[len+2+pipeLocation], O_WRONLY | O_APPEND | O_CREAT, 0600);
        dup(1);
        dup2(f, 1);
        close(f);
      }
      exec = execvp(args2input[0], args2input);
      if (exec<0){
        perror("stdinRedirect fail: error B");
        exit(1);
      }
      
      return 0;
  }
}

int redir(char* args[], int argsLen){
  char* path;
  int MetalPipe = 0;
  int pipeLocation = 0;
  int stdoutRedir = 0;
  int stdinRedir = 0;
  for (int i = 0; i<argsLen; i++){
    if (strcmp(args[i], "|") == 0){
        MetalPipe = 1;
        args[i] = NULL;
        pipeLocation = i;
        break;
    }
  }
  if(MetalPipe != 1){
    for (int i = 0; i<argsLen; i++){
      if(MetalPipe == 1){
        break;
      }
      if (strcmp(args[i], ">") == 0){
        path = args[i+1];
        stdoutRedir = 1;
        args[i] = NULL;
        break;
      }
      if (strcmp(args[i], "<") == 0){
        path = args[i+1];
        stdinRedir = 1;
        args[i] = NULL;
        break;
      }
    }
  }
  if (MetalPipe == 1){
    PipeRedirExec(args, pipeLocation, argsLen);
    return 1;
  }
  if (stdoutRedir == 1){
    stdoutRedirExec(path, args);
    return 1;
  }
  else if (stdinRedir == 1){
    stdinRedirExec(path, args);
    return 1;
  }
  return 0;
}