#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <signal.h> 

void sigHandler (int);
 
//  Write a parent program that: 
int main() { 
  int fd[2]; 
  int pipeCreationResult; 
  int forkResult; 

//  Spawns off a child process 
  forkResult = fork(); 
    
  if(forkResult < 0) { // Fork Failed 
    perror("Fork failed"); 
    exit(1); 
  } 

//  Installs signal handler(s) for the two user-defined signals (SIGUSR1/SIGUSR2) 
signal (SIGUSR1, sigHandler);
signal (SIGUSR2, sigHandler);

//  When a user-defined signal is received, it reports the type of signal sent
if(forkResult == 0) {  // Child process 

  printf("\nSpawned child with PID [%ld]\n\n", (long)getpid());
  while(1){
    int x = rand() % 5;
    sleep(x);
    if(x % 2  == 0){
      raise(SIGUSR1);
    }
    else{
      raise(SIGUSR2);
    }
  }
}
else{
  printf("waiting...");
}  

//  note: it may be necessary to reinstall your signal handler after a signal is received 
//  Terminates gracefully upon receiving a Control-C 
   
  return 0; 
}


void sigHandler (int sigNum)  {  
  if (sigNum == SIGUSR1) {
    printf("received a SIGUSR1 signal.\n");
  }
  if (sigNum == SIGUSR2) {
    printf("received a SIGUSR2 signal.\n");
  }  
} 