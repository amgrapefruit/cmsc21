#include <stdio.h>


int main() {
    char str[] = "puta";
    char *tr = "ati";

    printf("%s %s\n", str, tr);

    str[1] = 'o';
    
    printf("%s %s %c\n", str, tr, tr[1]);
}