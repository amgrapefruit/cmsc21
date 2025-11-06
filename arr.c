#include <stdio.h>
#include <stdlib.h>


void printIntArr1(int *arr, int size) {
    printf("\n1\n");
    for (int i = 0 ; i < size ; i++) {
        printf("\n[%i] %i; ", i+1, arr[i]);
    }
}
void printIntArr2(int arr[], int size) {
    printf("\n2\n");
    for (int i = 0 ; i < size ; i++) {
        printf("\n[%i] %i; ", i+1, arr[i]);
    }
}
void printIntArr3(int arr[10], int size) {
    printf("\n3\n");
    for (int i = 0 ; i < size ; i++) {
        printf("\n[%i] %i; ", i+1, arr[i]);
    }
}
void printIntArr4(int arr[5], int size) {
    printf("\n4\n");
    for (int i = 0 ; i < size ; i++) {
        printf("\n[%i] %i; ", i+1, arr[i]);
    }
}

void printMultTable (int A[][10]) { // will int **A work ?
    printf (" Table \n") ;

    for ( int  i =0; i <10; i ++) {
        for ( int j =0; j <10; j ++) {
            printf ("%d ",A [ i ][ j ]) ;
            }
        printf ("\n") ;
    }
 }
 
 void printMults (int ***A) { // will int **A work ?
    printf (" Table \n") ;
    for (int k = 0; k < 10; k++) {

    
    for ( int  i =0; i <10; i ++) {
        for ( int j =0; j <10; j ++) {
            printf ("%d ",A [k][ i ][ j ]) ;
            }
        printf ("\n") ;
    }
    printf("\n\n");
}
 }

int main() {
    char str[] = "puta";
    char *tr = "ati";

    int mult[10][10];
/*
    int **mult;
    mult = (int **) malloc(sizeof(int *) * 10);

    for (int k = 0; k < 10; k++) {
        mult[k] = (int *) malloc(sizeof(int ) * 10);
    }*/

    int ***mults;
    mults = (int ***) malloc(sizeof(int **) * 10);

    for (int j = 0; j < 10; j++) {
        mults[j] = (int** ) malloc(sizeof(int*) * 10);
        for (int k = 0; k < 10; k++) {

        mults[j][k] = (int* ) malloc(sizeof(int) * 10);
        }
    }

    //int mults[10][10][10];

    int i , j ,k;

    // for each row in the table
    for( i =0; i <10; i ++) {
        // for each col in the table
        for( j =0; j <10; j ++) {
            mult [ i ][ j ] = i * j ;

            for (k = 0; k < 10; k++) {
                mults [i][j][k] = i*j*k;
            }
        }
    }  
    
    printMultTable ( mult ) ;
    //printMults(mults);
/*
    int *ints = (int *) malloc(sizeof(int) * 6); 
    ints[0] = 11;
    ints[1] = 22;
    ints[2] = 33;
    ints[3] = 44;
    ints[4] = 55;
    ints[5] = 66;

    printIntArr1(ints, 6);
    printIntArr2(ints, 6);
    printIntArr3(ints, 6);
    printIntArr4(ints, 7);*/
}