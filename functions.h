#ifndef FUNCTIONS_H
#define FUNCTIONS_H
void err();
void printCWD();
int parse_args( char * line, char ** arg_ary );
int redirection(int dest, int source);
int checkLessThan(char** argAry);
#endif
