#include <stdio.h>

int recursion(int num) {
    if (num <   0) return recursion(num*-1);

    if (num < 10) {
        return num;
    }

    else {
        return num % 10 + recursion(num/10);
    }

    
}

int main() {
    
    int val = 0;

    scanf("%i", &val);

    int print = recursion(val);

    printf("%i\n", print);
}

