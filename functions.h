#ifndef FUNCTIONS_H
#define FUNCTIONS_H
void err();
void printCWD();
char * parse_args( char * line, char ** arg_ary, char * fake );
int redirection(int source, int dest);
int checkLessThan(char** argAry);
#endif
