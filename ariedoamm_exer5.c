/**
 * Author: Aaron Michael M. Ariedo
 * Date: 16 September 2025
 * CMSC 21: Exercise 5
 */

#include <stdio.h>

int getInput(int *x, int *y);
int swapValues(int *x, int *y);
int primeChecker(int x);
int getLargest(int x, int y, int *largest1, int *largest2, int *largest3);
int printLargest(int *largest1, int *largest2, int *largest3);

int main() {
    int x = 0, y = 0; // pointers needed for swapping and input
    int largest1 = 0, largest2 = 0, largest3 = 0;

    while (1){
        x = 0;
        y = 0;
        largest1 = 0;
        largest2 = 0;
        largest3 = 0;

        if (getInput(&x, &y) == 0) {
            // if return is 0 (invalid)

            printf("Invalid range!\n\n");
            continue; // skip to next input
        }

        if (x > y) swapValues(&x, &y);

        getLargest(x, y, &largest1, &largest2, &largest3);
        
        printLargest(&largest1, &largest2, &largest3);
    }

    return 0;
}

// get int inputs for int pointers x and y
int getInput(int *x, int *y) {
    // get x
    printf("Enter x: ");
    scanf("%i", x);

    // get y
    printf("Enter y: ");
    scanf("%i", y);

    // check for valid inputs
    if (*x > 1 || *y > 1) {
        return 1; // valid input

    } else return 0; // invalid input
}

// function for swapping int values
int swapValues(int *x, int *y) {
    int z = *x;
    *x = *y;
    *y = z;
}

// function for checking prime
int primeChecker(int x) {
    // 1 is not a prime number
    if (x == 1) return 0;
    
    // iterate thru all ints until x
    for (int i = 2; i < x; i++){

        // check if x is divisible by i
        // ie x is not prime
        if (x % i == 0) {
            return 0;
        }
    }

    // x is not divisible by any number other than 1 and x is
    return 1;

}

// given 2 ints, find 3 largest prime integers between them
int getLargest(int x, int y, int *l1, int *l2, int *l3) {
    // iterate over all numbers from x to y
    for (int i = x; i <= y; i++) {
        if (primeChecker(i)) {

            // record as l1 > l2 > l3
            swapValues(l2, l3);
            swapValues(l2, l1);
            *l1 = i;
        }
    }

    return 1;
}

// print the largest numbers
int printLargest(int *largest1, int *largest2, int *largest3) {
    // print prime numbers
    // 0 is an invalid input
    // a 0 value means it was not assigned a prime number
    if (*largest1 == 0) {
        printf("No prime numbers were found\n\n");

    } else if (*largest2 == 0) {
        printf("There is one prime number: %i\n\n", *largest1);
    
    } else if (*largest3 == 0){
        printf("There are two prime numbers: %i %i\n\n", *largest1, *largest2);

    } else{
        printf("The three largest prime numbers are: %i %i %i\n\n", *largest1, *largest2, *largest3);

    }

    // no errors
    return 1;
}