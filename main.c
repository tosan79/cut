#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* fp = fopen("/proc/stat", "r");
    FILE* fp2 = fopen("./out", "w+");
    char c = fgetc(fp);
    while (c != EOF) {
        fputc(c, fp2);
        c = fgetc(fp);
    }
    fclose(fp);
    fclose(fp2);
}