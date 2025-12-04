#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
 if (argc != 2) {
    printf("USAGE: partc FILEIN\n");
    return 1;
 }

 char *filein = argv[1];

 int pipefd[2];
 
 if (pipe(pipefd) < 0) { 
    printf("ERROR: pipe failed\n");
    return 1; 
 }
 pid_t pid = fork();

 if (pid < 0) { 
    printf("ERROR: fork failed\n");
    return 1;
 }

 if (pid > 0) {
    close(pipefd[0]);

    dup2(pipefd[1],STDOUT_FILENO);
    close(pipefd[1]);

    char *args[] = {"./parta", filein, NULL};
    execv("./parta",args);

    printf("ERROR: exec parta failed\n");
    return 1;
 }

 else {
    close(pipefd[1]);
    dup2(pipefd[0],STDIN_FILENO);
    close(pipefd[0]);

    char *sort_args[] = {"sort", "-t,","-k2","-n", NULL};

    execvp("sort", sort_args);
    printf("ERROR: exec sort failed\n");
    return 1;
 }
return 0;
}
