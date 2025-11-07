#include <stdlib.h>
#include <stdio.h>

int main() {
    FILE *fptr = fopen("buyers.txt", "w");

    fprintf(fptr, "");

    fclose(fptr);
}