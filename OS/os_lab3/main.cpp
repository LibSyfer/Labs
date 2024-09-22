/*C++ Program for Bitonic Sort. Note that this program
works only when size of input is a power of 2. */

#include <iostream>

void printm(int a[], int N) {
    for(int i = 0; i < N; ++i) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

typedef struct Data {
    int* a;
    int low;
    int cnt;
    int dir;
} Data;

/*The parameter dir indicates the sorting direction, ASCENDING
or DESCENDING; if (a[i] > a[j]) agrees with the direction,
then a[i] and a[j] are interchanged.*/
void compAndSwap(int a[], int i, int j, int dir) {
    if(dir == (a[i] > a[j]))
        std::swap(a[i], a[j]);
}

/*It recursively sorts a bitonic sequence in ascending order,
if dir = 1, and in descending order otherwise (means dir=0).
The sequence to be sorted starts at index position low,
the parameter cnt is the number of elements to be sorted.*/
void bitonicMerge(int a[], int low, int cnt, int dir) {
    if(cnt > 1) {
        int k = cnt / 2;
        for(int i = low; i < (low+k); ++i) {
            compAndSwap(a, i, i+k, dir);
        }
        bitonicMerge(a, low, k, dir);
        bitonicMerge(a, low+k, k, dir);
    }
}

/* This function first produces a bitonic sequence by recursively
sorting its two halves in opposite sorting orders, and then
calls bitonicMerge to make them in the same order */

void* bitonicSort(void* data_) {
    Data* data = (Data*)data_;
    int* a = data->a;
    int low = data->low;
    int cnt = data->cnt;
    int dir = data->dir;

    if(cnt > 1) {
        int k = cnt/2;

        // sort in ascending order since dir here is 1
        pthread_t thread1, thread2;
        
        Data newData1;
        newData1.a = a;
        newData1.low = low;
        newData1.cnt = k;
        newData1.dir = 1;

        if(pthread_create(&thread1, NULL, bitonicSort, &newData1)) {
            std::cout << "Error thread1" << std::endl;
            return NULL;
        }

        // sort in descending order since dir here is 0
        Data newData2;
        newData2.a = a;
        newData2.low = low+k;
        newData2.cnt = k;
        newData2.dir = 0;

        if(pthread_create(&thread2, NULL, bitonicSort, &newData2)) {
            std::cout << "Error thread2" << std::endl;
            return NULL;
        }

        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);

        // Will merge wole sequence in ascending order
        // since dir=1.
        bitonicMerge(a,low, cnt, dir);
    }
    return NULL;
}

/* Caller of bitonicSort for sorting the entire array of
length N in ASCENDING order */
void sort(int a[], int N, int up) {
    Data data;
    data.a = a;
    data.low = 0;
    data.cnt = N;
    data.dir = up;

    bitonicSort(&data);
}

// Driver code
int main() {

    int a[100];
    int N = 0;

    int num;
    size_t i = 0;
    size_t j = 2;
    while(true) {
        if(!(std::cin >> num)) {
            if(i < j) {
                for(size_t k = i; k < j; ++k) {
                    a[k] = 0;
                }
            }
            N = j;
            break;
        }
        if(i == j) {
            j *= 2;
        }
        a[i] = num;
        ++i;
    }

    int up = 1; // means sort in ascending order
    sort(a, N, up);

    std::cout << "Sorted Array:" << std::endl;
    printm(a, N);
    return 0;
}
