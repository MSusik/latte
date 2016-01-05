#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error() {
    fprintf(stderr, "runtime error\n");
}

void printString(char *str) {
    printf("%s\n", str);
}

char* GVl43xXD1cE6h6LYIjas(char* str1, char* str2)
{
    //DEBUG
    //printString(str1);
    //printString(str2);
    fflush(stdout);

    size_t len1 = strlen(str1), len2 = strlen(str2);

    // who cares about freeing memory?
    char *concat = (char*) malloc(len1 + len2 + 1);

    memcpy(concat, str1, len1);
    memcpy(concat+len1, str2, len2+1);
    return concat;
}

void printInt(int x) {
    printf("%d\n", x);
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
