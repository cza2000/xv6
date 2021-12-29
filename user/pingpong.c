#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    // parent -> child
    int fd1[2];
    // child -> parent
    int fd2[2];
    pipe(fd1);
    pipe(fd2);
    int pid = fork();
    if (pid == 0)
    {
        // child process
        char buf[512];
        int n = read(fd1[0], buf, sizeof buf);
        buf[n] = '\0';
        printf("%d: received ping\n", getpid());
        write(fd2[1], "pong", sizeof(char) * 4);
        exit(0);
    }
    else
    {
        write(fd1[1], "ping", (sizeof(char)) * 4);
        char buf[512];
        int n = read(fd2[0], buf, sizeof buf);
        buf[n] = '\0';
        printf("%d: received pong\n", getpid());
        wait((int *)0);
        exit(0);
    }
}