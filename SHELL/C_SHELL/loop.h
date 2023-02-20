#include "line.h"
#include "execute.h"


void myshell_loop(void){
    char *line;
    char **args;
    int status;

    do{

        printf(">");
        line = myshell_readline();
        args = myshell_split_line(line);
        status = myshell_launch(args);

        //freeing up the buffer
        free(line);
        free(args);

    }while(status);
}