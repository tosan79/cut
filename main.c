#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define STAT_MAX_LEN 4000

char buffer[STAT_MAX_LEN];

void Reader() {
    FILE* fp = fopen("/proc/stat", "r");
    char c = fgetc(fp);
    int i = 0;
    while (c != EOF) {
        buffer[i] = c;
        c = fgetc(fp);
        i++;
    }
    fclose(fp);
    printf("%s", buffer);
}

int main() {
    Reader();
}