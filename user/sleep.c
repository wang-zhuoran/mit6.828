#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(2, "Usage: sleep <number>\n");
        exit(1);
    }
    else
    {
        int time = atoi(argv[1]); // argv[0] is the name of the program
        // printf("sleeping for %d ticks\n", time);
        sleep(time);
        exit(0);
    }
    
}