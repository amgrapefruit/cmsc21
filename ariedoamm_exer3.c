/**
 * Author: Aaron Michael M. Ariedo
 * Date: 14 September 2025
 * CMSC 21: Exercise 3
 */

#include <stdio.h>
#include <math.h>

int menu();
float compute(float population, float rate, int years);

int main() {
    
    int choice = 0; // user input to compute or exit

    // main loop
    while (1) {
        choice = menu();

        if (choice == 2) {
            break; // user chose to exit
        }

        else if (choice == 1) {
            // user chose to compute
            float population = 0, rate = 0;
            int years = 0;

            // input population
            while (1) {
                printf("Enter population (n): ");
                scanf("%f", &population);

                if (population >= 0) {
                    break;
                }

                printf("Please input a non-negative number.\n");
            }

            // input growth rate
            printf("Growth rate (y%%): ");
            scanf("%f", &rate);

            // input years
            while(1) {
                printf("Years (x): ");
                scanf("%i", &years);

                if (years >= 0) {
                    break;
                }

                printf("Please input a non-negative number.\n");

            }

            // display results
            printf("After %i year(s) at a %.0f%% growth rate, the population will be %.2f\n\n", years, rate, roundf(compute(population, rate, years)*100)/100);
        }

        else {
            // user did not input a valid option
            printf("Invalid input!\n\n");
        }
    }

    return 0;
}

int menu(){

    // print texts
    printf("============================\n");
    printf("POPULATION GROWTH CALCULATOR\n");
    printf("[1] Compute\n");
    printf("[2] Exit\n");
    printf("Enter choice: ");

    // get user choice and return
    int choice = 0;
    scanf("%i", &choice);

    return choice; 
}

float compute(float population, float rate, int years) {

    // base case
    if (years == 0) {
        return population;
    }

    // recursive case
    else {
        return compute(population, rate, years - 1)*(rate/100 + 1);
    }
}