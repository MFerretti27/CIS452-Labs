
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
   int fd = open("tmp.txt", O_WRONLY | O_APPEND);

   printf("tmp.txt fd = %d\n", fd);

   dup2(fd, 1);

   printf("This string will be printed in tmp.txt file\n");

   int forkResult = fork();

   if(forkResult == 0) {  // Child process
        printf("\nSpawned child with PID [%ld]\n\n", (long)getpid());
        char *argument_list[] = {"ls", "-a", NULL}; // NULL terminated array of char* strings
        execvp("ls", argument_list); // Child Executes Command
   }

   exit(EXIT_SUCCESS);
}

