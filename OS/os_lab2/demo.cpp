#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include <errno.h>


unsigned int fib(unsigned int n) {
    if (n < 2) {
        return n;
    } else {
        int num_1, num_2;
        int fd[2]; // файловые дескрипторы для функции системного вызова pipe
        if (pipe(fd) < 0) {
            printf("pipe error\n"); // сообщаем об ощибке pipe
        }

        pid_t id = fork(); //создаем дочерний процесс
        if (id < 0) {
            printf("fork error\n"); // сообщаем об ошибке fork
        } else if (id == 0) { // дочерний процесс
            int num_1 = fib(n - 2);
            if(write(fd[1], &num_1, 4) < 4) { //записываем число num_1 в файл
                printf("write error\n"); // сообщаем об ошибке записи
            }
            close(fd[1]); // закрываем поток записи
            close(fd[0]); // закрываем поток чтения
            exit(1);
        } else { // родительский процесс
            num_1 = fib(n - 1);
            wait(NULL); // ждем завершения выполнения дочернего процесса
            if(read(fd[0], &num_2, 4) < 4) { // записываем число, полученное в дочернем потоке в переменную num_2
                printf("read error\n"); // сообщаем об ошибке чтения
            }
            close(fd[1]); // закрываем поток записи
            close(fd[0]); // закрываем поток чтения
        }
        return (num_1 + num_2);
    }
}

int main(int argc, char* argv[]) {
    unsigned int num;
    printf("Enter number: ");
    scanf("%u", &num);

    printf("Fib: %u\n", fib(num));

    printf("%d\n", errno);
    return 0;
}
