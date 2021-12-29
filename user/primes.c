#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void get_primes(int fd1[])
{
    close(fd1[1]);
    int nums[35];
    int first = -1;
    int n = read(fd1[0], &first, sizeof(int));
    if (n == 0)
    {
        exit(0);
    }
    printf("prime %d\n", first);
    int tmp = 0;
    int idx = 0;
    while (n > 0)
    {
        n = read(fd1[0], &tmp, sizeof(int));
        if (n > 0)
        {
            if (tmp % first != 0)
            {
                nums[idx++] = tmp;
            }
        }
    }

    close(fd1[0]);
    if (nums[0] == 0)
    {
        exit(0);
    }

    int fd2[2];
    pipe(fd2);
    int pid = fork();
    if (pid != 0)
    {
        write(fd2[1], nums, idx * sizeof(int));
        close(fd2[1]);
        wait(0);
        exit(0);
    }
    else
    {
        get_primes(fd2);
    }
}

int main(int argc, char *argv[])
{
    int fd[2];
    pipe(fd);
    if (fork() != 0)
    {
        close(fd[0]);

        for (int i = 2; i < 36; i++)
        {
            int num = i;
            write(fd[1], &num, sizeof(int));
        }

        close(fd[1]);
        wait(0);
        exit(0);
    }
    else
    {
        get_primes(fd);
    }
    return 0;
}
