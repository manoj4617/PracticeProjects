#include "builtin_cmd.h"

int myshell_launch(char **args){

    pid_t pid, wpid;
    int status;

    pid = fork();

    if(pid == 0){
        
        /*
        it means it is a child process
        fork() creates creates a new process out of the parent
         process, the newly created process is called "child" process
         and fork() return 0 to the child process and the process id (PID)
         of the child process to the parent process
         And both the processes execute at the same time   
        */
        if(execvp(args[0], args) == -1){
            //exit forking
            perror("myshell");
        }
        else{
            //parent process
            do{
                wpid = waitpid(pid, &status,WUNTRACED);
            }while(!WIFEXITED(status) && !WIFSIGNALED(status));
        }

    }

    return 1;
}

char *builtin[] = {
    "cd",
    "help",
    "exit",
    "mkdir"
};


int (*builtin_func[])(char**) = {
    &myshell_cd,
    &myshell_help,
    &myshell_exit,
    &myshell_mkdir
};

int myshell_num_builtins() {
  return sizeof(builtin) / sizeof(char *);
}

//to execute builtin shell commands
int myshell_execute(char **args){
    
    if(args[0] == NULL){
        return 1;
    }
    
    for(int i=0;i < myshell_num_builtins(); ++i){
        if(strcmp(args[0], builtin[i]) == 0){
            return (*builtin_func[i])(args);
        }
    }

    return myshell_launch(args);
}

