#include <stdio.h> // ввод, вывод
#include <sys/stat.h> // функция fstat
#include <sys/types.h> // различные типы(pid_t)
#include <sys/wait.h> // функция wait
#include <sys/mman.h> // функция mmap
#include <fcntl.h> // функция open
#include <unistd.h> // функция close
#include <stdlib.h> // функция exit

#include <errno.h>

void MSort(char* arr, size_t size); // Построчная сортировка файла(символьная)

int main(int argc, char *argv[]) {
    if(argc != 3) return 1;

    int fin1, fin2; // Файловые дискрипторы файлов 1 и 2

    void *img1, *img2; // Указатели на область в памяти файлов 1 и 2
    size_t sizeFile1, sizeFile2; // Размер файлов 1 и 2

    if((fin1 = open(argv[1], O_RDWR)) == -1) return 2;
    if((fin2 = open(argv[2], O_RDWR)) == -1) return 2;

    struct stat statbuf;
    if(fstat(fin1, &statbuf) < 0) {fprintf(stderr, "Ошибка выполнения функции fstat\n"); return 4;}
    sizeFile1 = statbuf.st_size;
    if(fstat(fin2, &statbuf) < 0) {fprintf(stderr, "Ошибка выполнения функции fstat\n"); return 4;}
    sizeFile2 = statbuf.st_size;

    if((img1 = mmap(0, sizeFile1, PROT_READ | PROT_WRITE, MAP_SHARED, fin1, 0)) == MAP_FAILED) {fprintf(stderr, "Ошибка выполнения функии mmap\n"); return 5;}
    if((img2 = mmap(0, sizeFile2, PROT_READ | PROT_WRITE, MAP_SHARED, fin2, 0)) == MAP_FAILED) {fprintf(stderr, "Ошибка выполнения функии mmap\n"); return 5;}

    char *symbolsImg1 = (char*)img1;
    char *symbolsImg2 = (char*)img2;

    /******     Sorting files and print it       ******/

    pid_t pid1, pid2;

    pid1 = fork();
    pid2 = fork();

    if(pid1 < 0) {
        return 7;
    } else if(pid1 == 0) { // дочерний процесс при первом вызове fork
        if(pid2 < 0) {
            fprintf(stderr, "Не удалось создать дочерний процесс в дочернем процессе\n");
            exit(1);
        } else if(pid2 == 0) { // Процесс для обработки первого файла
            MSort(symbolsImg1, sizeFile1);
        } else { // Процесс для обратотки второго файла
            MSort(symbolsImg2, sizeFile2);
            wait(NULL);
        }
    } else { // родительский
        if(pid2 < 0) {
            fprintf(stderr, "Не удалось создать дочерний процесс в родительском процессе\n");
        } else if(pid2 == 0) {
        } else {
            wait(NULL);
            size_t i = 0;
            size_t k = 0;
            while(i < sizeFile1 || k < sizeFile2) {
                if(i < sizeFile1) {
                    while(symbolsImg1[i] != '\n') {
                        printf("%c", symbolsImg1[i]);
                        ++i;
                    }
                    ++i;
                    printf("\n");
                }
                if(k < sizeFile2) {
                    while(symbolsImg2[k] != '\n') {
                        printf("%c", symbolsImg2[k]);
                        ++k;
                    }
                    ++k;
                    printf("\n");
                }
            }
        }
    }

    /******                     ******/

    if(munmap(img1, sizeFile1) < 0) {fprintf(stderr, "Ошибка выполнения функции munmap\n"); return 10;}
    if(munmap(img2, sizeFile2) < 0) {fprintf(stderr, "Ошибка выполнения функции munmap\n"); return 10;}

    if(close(fin1) < 0) {fprintf(stderr, "Ошибка выполнения функции close\n"); return 12;}
    if(close(fin2) < 0) {fprintf(stderr, "Ошибка выполнения функции close\n"); return 12;}

    return 0;
}

void MSort(char* arr, size_t size) {
    char tmp;
    for(size_t i = 0; i < size; ++i) {
        for(size_t j = size-1; j > i; --j) {
            if(arr[j] == '\n') continue;
            if(arr[j-1] > arr[j]) {
                tmp = arr[j-1];
                arr[j-1] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}
