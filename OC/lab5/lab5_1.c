#include <stdio.h>
#include <stdlib.h>
#include "lab5_1.h"

int main() {
    char comand;
    while (scanf("%c", &comand) > 0) {
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
        else if (comand == EOF) exit(0);
        else if (comand == '\n' || comand == ' ') continue;
        else printf("Wrong format\n");
    }
}