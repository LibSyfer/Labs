#include <stdio.h>
#include <dlfcn.h>
#include "libstackdouble/stackDouble.h"

void (*_DStackCreate)(DStack*);
void (*_DStackPush)(DStack*, double);
Node* (*_DStackPop1)(DStack*);
double (*_DStackPop2)(DStack*);
size_t (*_DStackSize)(DStack*);
void (*_DStackDelete)(DStack*);

int loader(void *handle) {
    char *error;

    _DStackCreate = dlsym(handle, "DStackCreate");
    error = dlerror();
    if(error != NULL) {
        printf("!!! %s\n", error);
        return 2;
    }
    _DStackPush = dlsym(handle, "DStackPush");
    error = dlerror();
    if(error != NULL) {
        printf("!!! %s\n", error);
        return 3;
    }
    _DStackPop1 = dlsym(handle, "DStackPop1");
    error = dlerror();
    if(error != NULL) {
        printf("!!! %s\n", error);
        return 3;
    }
    _DStackPop2 = dlsym(handle, "DStackPop2");
    error = dlerror();
    if(error != NULL) {
        printf("!!! %s\n", error);
        return 3;
    }
    _DStackSize = dlsym(handle, "DStackSize");
    error = dlerror();
    if(error != NULL) {
        printf("!!! %s\n", error);
        return 3;
    }
    _DStackDelete = dlsym(handle, "DStackDelete");
    error = dlerror();
    if(error != NULL) {
        printf("!!! %s\n", error);
        return 4;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    void *handle;
    handle = dlopen("libstackdouble/libstdb.so", RTLD_LAZY);
    if(!handle) {
        printf("!!! %s\n", dlerror());
        return 1;
    }
    int n;
    if((n = loader(handle))) {
        return n;
    }

    DStack st;
    (*_DStackCreate)(&st);
    (*_DStackPush)(&st, 10.1);
    (*_DStackSize)(&st);
    printf("%f\n", (*_DStackPop2)(&st));
    (*_DStackDelete)(&st);
    dlclose(handle);

    return 0;
}
