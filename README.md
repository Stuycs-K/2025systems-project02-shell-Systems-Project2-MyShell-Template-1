[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Tfg6waJb)
# Systems Project2 - MyShell

Team Members: Gabriel, Patrick, Kartik

CREATIVE TEAM NAME: Triple Red-Green Colorblindness Shells

Features Successfully Implemented: 
<br/>
&emsp;Prompts user for input with directory path (starting with ~) and $
<br/>
&emsp;Quits terminal if "ctrl+d" or "exit" inputted
<br/>
&emsp;Runs commands with forking and execvp
<br/>
&emsp;Runs cd with chdir(), and no forking or execvp
<br/>
&emsp;Performs commands separated by semicolons in one line
<br/>
&emsp;Accepts redirection operators

Bugs: 
<br/>
&emsp;Currently pipes don't work

Function Headers:

shell.c - 
<br/>
&emsp;int main();

functions.c -
<br/>
&emsp;void err();
<br/>
&emsp;void printCWD();
<br/>
&emsp;int parse_args( char * line, char ** arg_ary );
<br/>
&emsp;int redirection(int source, int dest);
<br/>
&emsp;int run(char** argAry, int len);
