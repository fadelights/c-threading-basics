/* C program to demonstrate the use of `fork` in UNIX-based
operating systems.

The fork() function creates a new copy of the program
(with all its data until the point of the call)
called the "child" of the original process,
with the original process being called the "parent".

fork() doesn’t take any parameter and returns
an int value as following:

- Zero: if it is the child process (the process created).
- Positive value: if it is the parent process (pid of child process).
- Negative value: if an error occurred.

The parent can wait for the execution of the child to
finish by using the wait() system call.

Written by Arman Rezaei (9723034)
Amirkabir University of Technology
May 19, 2022
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


// auxiliary function for demonstration purposes
void f() {
    printf("(%d)\t f() call from pid %d\n", getpid(), getpid());
}
// ---------------------------------------------


int main() {

    pid_t pid = fork();
    printf("(%d)\t fork() was called in process %d which returned %d.\n", getpid(), getpid(), pid);

    if (pid == 0) {
        printf("(%d)\t I'm a child! (pid: %d)\n", getpid(), getpid());
    }

    else if (pid > 0) {
        printf("(%d)\t I'm the parent (pid: %d)--waiting for child to finish.\n", getpid(), getpid());
        wait(NULL); // wait for child to finish
        printf("(%d)\t Child execution finished.\n", getpid());
    }

    else // in case of error
        fprintf(stderr, "An error was encountered during fork operation.\n");

    f();

    if (pid > 0)
        printf("(%d)\t Parent execution finished.\n", getpid());

    return 0;
}
