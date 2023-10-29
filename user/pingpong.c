#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    char byte = 'a';
    int p1[2];
    int p2[2];
    pipe(p1);
    pipe(p2);
    if (fork() == 0) // child
    {
        read(p1[0], &byte, 1);
        int pid = getpid();
        printf("%d: received ping\n", pid);
        close(p1[0]);
        write(p2[1], &byte, 1);
        close(p2[1]);
        exit(0);
    }
    else // parent
    {
        write(p1[1], &byte, 1);
        close(p1[1]);
        read(p2[0], &byte, 1);
        close(p2[0]);
        int pid = getpid();
        printf("%d: received pong\n", pid);
        exit(0);
    }
}