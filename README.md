# client-server-chat
c program using system calls fork, execve, wait, mkfifo, mknod, unlik, chmod, gethostbyname, access, signal
The system calls: fork(2), execve(2)/ execlp(3) and wait(2)/waitpid(2) to fork and exec the clear Unix command.
The C library function mkfifo(3) or the system call mknod(2) and system call unlink(2) to make the named pipe and later remove it.
The system call chmod(2) to set the permissions on the FIFO
The C Library call gethostbyname(3) to get the hostname of the machine. Alternatively you may use the getenv(3) call to get the HOSTNAME environment variable.
The system calls access(2) and/or stat(2) to test for the existence of the named pipe. (The if [ -p "$pf" ]; then... test)
The system calls signal(2) or sigaction(2) to handle the trapping the the Ctrl-C in the listen program.
