#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pwd.h>
#include <sys/types.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64

#define MAX_TOKENS 80




char** tokenize(char* input_string) {
    char** tokens = malloc(MAX_TOKENS * sizeof(char*));
    char* token;
    int i = 0;

    token = strtok(input_string, " \t\n"); 
    while (token != NULL) {
        tokens[i] = token;
        i++;
        token = strtok(NULL, " \t\n");
    }
    tokens[i] = NULL; 
    return tokens;
}



void execute_command(char** tokens) {
    if (tokens[0] == NULL) {
        return;
    }

    pid_t pid = fork();

    if (pid == 0) {
        if (execvp(tokens[0], tokens) == -1) {
            perror("Fuck off");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("Go to hill ");
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
}

int main()
{
    char input[MAX_INPUT];
    char* buf[MAX_ARGS];
    


 struct passwd *pw;
    uid_t uid;

    uid = getuid();

    pw = getpwuid(uid);




   while (1) {

    printf("%s :$ ", pw->pw_name);
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break; 
        }

        char** tokens = tokenize(input);

        execute_command(tokens);

        free(tokens);
    }

   return 0;
}


