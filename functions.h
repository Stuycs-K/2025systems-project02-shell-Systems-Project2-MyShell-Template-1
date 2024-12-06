#ifndef FUNCTIONS_H
#define FUNCTIONS_H
void err();
void printCWD();
int parse_args( char * line, char ** arg_ary );
int redirection(int source, int dest);
int run(char** argAry, int len);
#endif
