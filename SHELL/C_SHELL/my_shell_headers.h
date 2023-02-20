#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<unistd.h>

#define BUFFERSIZE 1024
#define TOKEN_BUFFER_SIZE 64
#define TOKEN_DEL " \t\n\r\a"

//functions to execute shell builtin commands
int myshell_cd(char **args);
int myshell_help(char **args);
int myshell_exit(char **args);
int myshell_mkdir(char **args);
int myshell_num_builtins();



void myshell_loop(void);
char* myshell_readline(void);
char** myshell_split_line(char* line);
int myshell_launch(char **args);
int myshell_execute(char **args);