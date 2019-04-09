#include <stdio.h> 
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h> 
#include <signal.h>
#include <netdb.h>

#define BUFSIZE		4096

char * check = "/var/tmp/listen";

void cat(void)
{
  char buf[BUFSIZE];
  int r;
  int fd = open(check, O_WRONLY);

  while((r = read(fd, buf, BUFSIZE)) > 0) {
    // Don't use BUFSIZE for the count of data to write, use r:
    write(STDOUT_FILENO, buf, r);
    close(fd);
  }
}


void handler(int sig)
{
 signal(sig, &handler);
 unlink(check);
 exit(1);   
}


int main(int argc, char *argv[])
{
 int status;
 char * hostname = getenv("HOSTNAME");
 int fd;
// struct hostent *hostname;
   
  if (access(check, F_OK) != 0){
   mkfifo(check, 0666);
   chmod(check, S_IWOTH | S_IWGRP | S_IXOTH);
  }
  else
     {
   printf("Listen is already running, exiting.\n");
   exit(1);
  }   
  
  if (access(check, F_OK) == 0){
    signal(SIGINT, &handler);
  }
  //forks creates a child process
  pid_t pid = fork();
  if (pid < 0){
    perror("fork");
    return -1;
  }
  //In the child we will exec the clear command
  if (pid == 0){
   //execve("/usr/bin/clear", argv, NULL);
    execlp("/usr/bin/clear","/usr/bin/clear", argv, NULL);
    perror("exec");
  }
  // In the parent, we will wait for the ls to complete before continuing:
  waitpid(pid, &status, 0);   
   if (hostname)
   printf("Login to %s and use 'say' to anonymously chat to this terminal:\n", hostname);  
   while(1) cat();
  

 return 0;   
}
 