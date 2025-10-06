/**
 * Author: Aaron Michael M. Ariedo
 * Date: 2 october 2025
 * CMSC 21: Exercise 6
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Function to compute the Pearson correlation coefficient
void printMatrix(int rows, int columns, double **mat){

    printf("\n--------------------------------------------------------------\n");
    //printf("x\t\t|\ty\t\t|\tx^2\t\t|\ty^2\t\t|\txy\n");
	printf("%9s | %9s | %9s | %9s | %9s\n","x","y","x^2","y^2","xy");	
    printf("--------------------------------------------------------------\n");
    
    // iterate over all rows
	for(int r = 0; r < rows; r++) {
        printf("%9.2f | %9.2f | %9.2f | %9.2f | %9.2f\n",
        mat[0][r],mat[1][r],mat[2][r],mat[3][r],mat[4][r]);
    }

    printf("--------------------------------------------------------------\n");
    
    //printf("%.2f\t|\t%.2f\t|\t%.2f\t|\t%.2f|\t%.2f\n",mat[10][0],mat[10][1],mat[10][2],mat[10][3],mat[10][4]);
	printf("%9.2f | %9.2f | %9.2f | %9.2f | %9.2f\n",
	        mat[0][10],mat[1][10],mat[2][10],mat[3][10],mat[4][10]);
    printf("--------------------------------------------------------------\n\n");
}

// Function to compute the Pearson correlation coefficient
double pearson_correlation(int size, double *x, double *y) {
   	/*code here*/
    double **matrix;
    int num_cols = 5;

    // array of cross products
    matrix = (double **) malloc(num_cols * sizeof(double *));
    
    for (int i = 0; i < num_cols; i++) {
        // make arrays per variable category
        matrix[i] = (double *) malloc(size * sizeof(double));
    }

    double sum = 0;

    // populate x sub array
    for (int j = 0; j < size + 1; j++) {
        // check if last element to record summation
        if (j == size) {
            matrix[0][j] = sum;
        }
        else { // non-last element
            matrix[0][j] = x[j];

            // continuously add to sum  
            sum += matrix[0][j];
        }  
    }

    sum = 0; // reset sum

    // populate y sub array
    for (int j = 0; j < size + 1; j++) {
        // check if last element to record summation
        if (j == size) {
            matrix[1][j] = sum;
        }
        else { // non-last element
            matrix[1][j] = y[j];

            // continuously add to sum  
            sum += matrix[1][j];
        }  
    }

    sum = 0; // reset sum

    // solve for x^2 sub array
    for (int j = 0; j < size + 1; j++) {
        // check if last element to record summation
        if (j == size) {
            matrix[2][j] = sum;
        }
        else { // non-last element
            matrix[2][j] = x[j] * x[j];

            // continuously add to sum  
            sum += matrix[2][j];
        }  
    }

    sum = 0; // reset sum

    // solve for y^2 sub array
    for (int j = 0; j < size + 1; j++) {
        // check if last element to record summation
        if (j == size) {
            matrix[3][j] = sum;
        }
        else { // non-last element
            matrix[3][j] = y[j] * y[j];

            // continuously add to sum  
            sum += matrix[3][j];
        }  
    }

    sum = 0; // reset sum

    // solve for xy sub array
    for (int j = 0; j < size + 1; j++) {
        // check if last element to record summation
        if (j == size) {
            matrix[4][j] = sum;
        }
        else { // non-last element
            matrix[4][j] = x[j] * y[j];

            // continuously add to sum  
            sum += matrix[4][j];
        }  
    }

    printMatrix(size, num_cols, matrix);

    double numerator = size*matrix[4][size] - matrix[0][size]*matrix[1][size];
    double denominator = sqrt((size*matrix[2][size] - matrix[0][size]*matrix[0][size])*(size*matrix[3][size] - matrix[1][size]*matrix[1][size]));

    return numerator / denominator;
}

// function declarations for additional functions
void insertData(double *lengths, double *weights);
void interpretPearson(double correlation);

int main() {
    // Define the arrays for the first and second columns
    // pointers for dynamic allocations
    double *weights;
    double *lengths;    
   
    // Determine the number of rows (assumed both columns have the same length)
    int num_rows = 10;

    weights = (double *) malloc(num_rows * sizeof(double));
    lengths = (double *) malloc(num_rows * sizeof(double));

    if (weights == NULL || lengths == NULL) {
        printf("An error occured in memory allocation.\n");
        return 0;
    }

    insertData(lengths, weights);

    // Print the array with 2 columns
    printf("Weight(Kg)\tLength(cm))\n");
    for (int i = 0; i < num_rows; i++) {
        printf("%.2f\t\t%.1f\n", weights[i], lengths[i]);
    }

    // Calculate Pearson correlation coefficient
    double correlation = pearson_correlation(num_rows, weights, lengths);
    printf("Pearson Correlation Coefficient: %.2f\n\n", correlation);

    //print interpretation here
    interpretPearson(correlation);

    return 0;
}

void interpretPearson(double correlation) {
    // print corresponding interpretations
    if (correlation > 0.5) {
        printf("The data has a strong positive correlation.\n");
    } else if (correlation > 0.3) {
        printf("The data has a moderate positive correlation.\n");
    } else if (correlation > 0) {
        printf("The data has a weak positive correlation.\n");
    } else if (correlation == 0) {
        printf("Data has no correlation\n");
    } else if (correlation >= -0.3) {
        printf("The data has a weak negative correlation.\n");
    } else if (correlation >= -0.5) {
        printf("The data has a moderate negative correlation.\n");
    } else { // correlation is less than 0.5
        printf("The data has a strong negative correlation.\n");
    }
}

void insertData(double *lengths, double *weights) {
    lengths[0] = 53.1;
    lengths[1] = 49.7;
    lengths[2] = 48.4;
    lengths[3] = 54.2;
    lengths[4] = 54.9;
    lengths[5] = 43.7;
    lengths[6] = 47.2;
    lengths[7] = 45.2;
    lengths[8] = 54.4;
    lengths[9] = 50.4;

    weights[0] = 3.63;
    weights[1] = 3.02;
    weights[2] = 3.82;
    weights[3] = 3.42;
    weights[4] = 3.59;
    weights[5] = 2.87;
    weights[6] = 3.03;
    weights[7] = 3.46;
    weights[8] = 3.36;
    weights[9] = 3.3;
}