#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void primes(int *fd){
    int p, d;
    // 关闭写
    close(fd[1]);
    if(read(fd[0], (void *)&p, sizeof(p)) != sizeof(p)){
        fprintf(2, "Read fail!\n");
        exit(1);
    }
    printf("prime %d\n", p);
    if (read(fd[0], (void *)&d, sizeof(d))){
        int fd1[2];
        pipe(fd1);
        if (fork() == 0){
            primes(fd1);
        }else{
            // 关闭读
            close(fd1[0]);
            do{
                if (d % p != 0){
                    write(fd1[1], (void *)&d, sizeof(d));
                }
            }while(read(fd[0], (void *)&d, sizeof(d)));
            // 关闭读
            close(fd[0]);
            // 关闭写
            close(fd1[1]);
            wait(0);
        }
    }
    exit(0);
}

int main(int argc, char *argv[]){
    int fd[2];
    pipe(fd);
    if (fork() == 0){
        primes(fd);
    }else{
        close(fd[0]);
        for (int i = 2; i <= 35; i++){
            if (write(fd[1], (void *)&i, sizeof(i)) != 4){
                fprintf(2, "Write fail!\n");
                exit(1);
            }
        }
        close(fd[1]);
        wait(0);
    }
    
    exit(0);
}