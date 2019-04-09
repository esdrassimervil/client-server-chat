#include <stdio.h> 
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h> 

#define BUFSIZE	4096

void cat(void)
{
  int r, w, t;
  char buf[BUFSIZE];
  char * listen = "/var/tmp/listen";
  int fd = open(listen, O_WRONLY);

  // Read up to BUFSIZE number of bytes from the input descriptor (fd):
  while((r = read(STDIN_FILENO, buf, BUFSIZE)) > 0) {
    // Make sure that every byte read is written to stdout (descriptor 1):
    t = 0;
    do {
      w = write(fd, buf+t, r-t);
      t += w;
    } while (t < r);
  }
  if (r < 0) perror("read");
   close(fd);
}

int main(int argc, char *argv[])
{
  char * listen = "/var/tmp/listen";
  
  if (access(listen, F_OK) != 0){
      printf("No one is listening.\n");
  }  else{
    printf("Write your message, type Ctrl-D to quit:\n");  
    cat();
  }
} 