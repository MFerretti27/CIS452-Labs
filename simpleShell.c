#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    while (1) {
        pid_t forkResult;
        struct rusage usage; // Used to getrusage function
        char userInput[50];
        int status = 0; // Used to wait for child to finish

        // Display a prompt to the user
        puts("\nPlease enter Command to run (Enter \"quit\" to stop)");

        // Receive and parse the user input
        fgets(userInput, 50, stdin); // Read a line into a character array (preferably using fgets())
        userInput[strlen(userInput) - 1] = '\0'; // Removes newline
   
        if ((strcmp(userInput, "Quit") == 0) || (strcmp(userInput, "quit") == 0)) {
            printf("User Entered Quit\n\n");
            exit(0);
        }

        // Tokenize the line using by using strtok(), splits a string into multiple based on separators
        char *word_1 = strtok(userInput, " ");
        char *word_2 = strtok(NULL, " ");  //  Continues tokenizing users input

        //printf("\nWord1: [%s]\n", word_1); // Used for debugging, seeing how its tokenized
        //printf("Word2: [%s]\n\n", word_2);

        // Spawn a child process to execute the command
        forkResult = fork();
        if (forkResult == 0) {
            printf("I am child with PID [%ld] Obeying your command\n\n", (long)getpid());

            char *argument_list[] = {word_1, word_2, NULL}; // NULL terminated array of char* strings

            // Child Executes Command
            execvp(word_1, argument_list);
            exit(0);
        }

        // Find and use the appropriate system call to collect resource usage statistics about each executed process
        if (forkResult > 0) {
            wait(&status); // Wait for child to die
            printf("\nI am Parent with PID [%ld] Tracking Child's Statistics\n", (long)getpid());

            getrusage(RUSAGE_CHILDREN, &usage);
            printf("\tChild's CPU time: %ld.%06d sec user, %ld.%06d sec system\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec,
               usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);

            printf("\tNumber of involuntary context switches experienced by each individual child process: %ld\n", usage.ru_nivcsw);
        }

        // Repeat until the user enters “quit"
    }
    return 0;
}




