#include "my_shell_headers.h"

int myshell_cd(char **args){

    if(args[0] == NULL){
        fprintf(stderr, "myshell:Expected argument to \"cd\"\n");
    }
    else{
        if(chdir(args[1]) != 0){
            perror("myshell");
        }
    }
}

char *builtin_str[] = {
    "cd",
    "help",
    "exit",
    "mkdir"
};

int myshell_help(char **args){
    int i;
    printf("Manoj's shell\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (i = 0; i < myshell_num_builtins(); i++) {
        printf("  %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}

int myshell_exit(char **args){
    return 0;
}

int myshell_mkdir(char **args){

    if(args[0] == NULL){
        fprintf(stderr, "myshell:Expecting argument to \"mkdir\"\n");
    }
    else{
        if(mkdir(args[1],S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0){
            perror("myshell");
        }
    }

    return 1;
}