#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    while (1)
    {
        char buf[512];
        int n;
        char tmp;
        int idx = 0;
        while (1)
        {
            n = read(0, &tmp, sizeof(char));
            if (n == 0)
            {
                break;
            }

            if (tmp == '\n')
            {
                buf[idx] = '\0';
                break;
            }

            buf[idx++] = tmp;
        }

        if (n == 0)
        {
            break;
        }

        char *new_argv[argc];
        for (int i = 0; i < argc - 1; i++)
        {
            new_argv[i] = argv[i + 1];
        }
        new_argv[argc - 1] = buf;

        if (fork() != 0)
        {
            wait(0);
        }
        else
        {
            exec(new_argv[0], new_argv);
        }
    }
    exit(0);
}