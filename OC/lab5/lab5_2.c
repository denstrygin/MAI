#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#define FIRST 1
#define SECOND 2

int curRealisation = SECOND;
void *libFD;
float (*der)(float, float);
int (*GCF)(int, int);
void (*whos_now)();
char *err = NULL;

void swapRealisaton(){
    if (dlclose(libFD) != 0) { 
        perror("Can't close dl");
        exit(1);
    }
    char *nextName;
    if (curRealisation == SECOND) {
        curRealisation = FIRST;
        nextName = "./libdyn1.so";
    }
    else {
        curRealisation = SECOND;
        nextName = "./libdyn2.so";
    }
    libFD = dlopen (nextName, RTLD_LAZY);
    if (!libFD) {
        perror("can't swap lib");
        exit(1);
    }
    der = dlsym(libFD, "der");
    if ((err = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", err);
        dlclose(libFD);
        exit(1);
    }
    GCF = dlsym(libFD, "GCF");
    if ((err = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", err);
        dlclose(libFD);
        exit(1);        
    }
    whos_now = dlsym(libFD, "whos_now");
    if ((err = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", err);
        dlclose(libFD);
        exit(1);        
    }
}

int main() {
    libFD = dlopen("./libdyn1.so", RTLD_LAZY);
    if (!libFD) {
        perror("can't swap lib");
        exit(1);
    }
    der = dlsym(libFD, "der");
    if ((err = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", err);
        dlclose(libFD);
        exit(1);
    }
    GCF = dlsym(libFD, "GCF");
    if ((err = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", err);
        dlclose(libFD);
        exit(1);        
    }
    whos_now = dlsym(libFD, "whos_now");
    if ((err = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", err);
        dlclose(libFD);
        exit(1);        
    }
    char comand;
    while(scanf("%c", &comand) > 0) {
        if (comand == '1') {
            int A, B;
            scanf("%d%d", &A, &B);
            printf("GCF = %d\n", GCF(A, B));
        }
        else if (comand == '2') {
            float A, deltax;
            scanf("%f%f", &A, &deltax);
            printf("der = %f\n", der(A, deltax));
        }
        else if (comand == '?') whos_now();
        else if (comand == '~') swapRealisaton();
        else if (comand == EOF) {
            dlclose(libFD);
            exit(0);
        }
        else if (comand == '\n' || comand == ' ') continue;
        else printf("Wrong format\n");
    }
}