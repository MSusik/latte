#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printInt(int x) {
    printf("%d\n", x);
}

void printString(char *str) {
    printf("%s\n", str);
}

void error() {
    fprintf(stderr, "runtime error\n");
}

int readInt() {
    int x;
    scanf("%d\n", &x);
}

char *readString() {
    char *res;
    scanf("%as\n", &res);
    return res;
}
