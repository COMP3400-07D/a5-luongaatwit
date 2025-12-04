#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
 if (argc != 3) {
    printf("USAGE: partb FILEIN FILEOUT");
    return 1;
}
char *filein = argv[1];
char *fileout = argv[2];

int fd = open(fileout, O_WRONLY | O_CREAT | O_TRUNC, 0770);

if (fd < 0) {
    printf("ERROR: cannot open %s\n", fileout);
    return 1;
}

dup2(fd,STDOUT_FILENO);
close(fd);

printf("Category,Count\n");
fflush(stdout);

char *args[] = {"./parta", filein, NULL};

execv("./parta",args);

printf("ERROR: exec failed\n");
return 1;
}
