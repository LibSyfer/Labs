#include <stdio.h>
#include "libstackdouble/stackDouble.h"

int main(int argc, char *argv[]) {
    DStack st;
    DStackCreate(&st);
    DStackPush(&st, 5.1);
    DStackSize(&st);
    printf("%f\n", DStackPop2(&st));
    DStackDelete(&st);
    return 0;
}
