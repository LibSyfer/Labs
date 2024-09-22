#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


long fibonacci(int num) {
    if(num == 0) {
        return 0;
    } else if(num == 1) {
        return 1;
    } else {
        pid_t pid = fork();
        if(pid < 0) {
            return 0;
        } else if(pid == 0) {
            long res = fibonacci(num-2);
            exit(res);
        } else {
            long parentRes = fibonacci(num-1);
            int status;
            wait(&status);
            long res = WEXITSTATUS(status);
            return (parentRes + res);
        }
    }
}

int main(int argc, char* argv[]) {
    int num;
    scanf("%d", &num);
    printf("fib[%d] = %d\n", num, fibonacci(num));
    return 0;
}
