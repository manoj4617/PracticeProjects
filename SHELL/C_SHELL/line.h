#include "my_shell_headers.h"


char* myshell_readline(void){

    int myshell_buffer_size = BUFFERSIZE;
    int position = 0;
    char* buffer = malloc(sizeof(char) * myshell_buffer_size);
    
    int c;

    // check for allocation failure
    if(!buffer){
        fprintf(stderr, "myshell: allocation error");
        exit(EXIT_FAILURE);
    }


    //run an infinite loop to read input from the user
    while(1){
        c = getchar();
        
        if(c == EOF || c == '\n'){
            buffer[position] = '\0';
            return buffer;
        }
        else{
            buffer[position] = c;
        }

        position++;

        if(position >= myshell_buffer_size){
            myshell_buffer_size += BUFFERSIZE;
            buffer = realloc(buffer, myshell_buffer_size);

            if(!buffer){
                fprintf(stderr, "myshell: Allocation error");
                exit(EXIT_FAILURE);
            }
        }
    }

}

char** myshell_split_line(char* line){

    int buffer_size = TOKEN_BUFFER_SIZE, position = 0;
    char **tokens = malloc(buffer_size * sizeof(char*));
    char *token;

    if(!tokens){
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    //split the line
    token = strtok(line, TOKEN_DEL);

    while(token != NULL){
        tokens[position] = token;
        position++;

        if(position >= buffer_size){
            buffer_size += TOKEN_BUFFER_SIZE;
            tokens = realloc(tokens, buffer_size * sizeof(char*));

            if(!tokens){
                fprintf(stderr, "Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, TOKEN_DEL);
    }

    tokens[position] = NULL;
    return tokens;

}