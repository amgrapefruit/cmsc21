/**
 * Author: Aaron Michael M. Ariedo
 * Date: 5 October 2025
 * CMSC 21: Exercise 7
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define STRLENGTH 50

int menu();
void start(char *name, int *num);
void inputNames(char **names, int num);
void flames(char *n1, char *n2, int index);
void freeStringArray(char **mat, int size);

int main() {
    int choice = 0; // for user input
    int names_filled = 0; // true or false if names array is filled

    int crush_num = 0; // for num of crushes
    char *my_name; // string for own name
    my_name = (char *) malloc(STRLENGTH * sizeof(char));
    
    start(my_name, &crush_num);
    
    char **names; // string array for crush names
    names = (char **) malloc(crush_num * sizeof(char *));

    while (1) {
        choice = menu();

        if (choice == 1) {
            // add names
            inputNames(names, crush_num);
            names_filled = 1;
        } else if (choice == 2 && names_filled == 1) {
            // iterate over all crush names
            for (int i = 0; i < crush_num; i++) {
                flames(my_name, names[i], i+1);
            }
        } else if (choice == 0) {
            // exit
            printf("Goodbye!");
            break;
        } else {
            printf("Invalid choice! ");

            if (!names_filled) {
                printf("The array is still empty.");
            }

            printf("\n\n");
        }
    }  

    freeStringArray(names, crush_num);
    return 0;
}

// print menu and scan for user choice
int menu(){
    printf("--------------------------------------\n");
    printf("[1] Input names\n");
    printf("[2] Compute FLAMES results\n");
    printf("[0] Exit\n");
    printf("--------------------------------------\n");
    printf("Choice: ");

    int choice = 0;
    scanf("%i%*c", &choice); // consume leftover new-line char
    printf("\n");

    return choice;
}

// ask for user name and number of crushes
void start(char *name, int *num) {
    printf("Enter your name: ");
    scanf("%[^\n]%*c", name);

    printf("Enter the number of your crushes: ");
    scanf("%i", num);
}

void inputNames(char **names, int num) {
    // populate string array
    for (int i = 0; i < num; i++) {
        // allocate memory for string
        names[i] = (char *) malloc(STRLENGTH * sizeof(char));
    
        // input name
        printf("Enter the name of crush #%i: ", (i+1));
        scanf("%[^\n]%*c", names[i]);
    }

    printf("\n");
}

void flames(char *n1, char *n2, int index) {
    printf("Crush #%i: %s\n", index, n2);

    // copy strings
    char name1[50];
    char name2[50];
    
    strcpy(name1, n1);
    strcpy(name2, n2);

    // iterate over all characters in first name
    for (int i = 0; i < strlen(name1); i++) {
        // skip on all non alphabets
        if (!isalpha(name1[i])){
            continue;
        }

        tolower(name1[i]);

        // find a similar char in second string
        for (int j = 0; j < strlen(name2); i++) {
            if (!isalpha(name2[j])){
                continue;
            }

            tolower(name2[j]);

            if (name1[i] == name2[j]) {
                // remove similar characters
                name1[i] = ' ';
                name2[j] = ' ';
                break;
            }
        }
    }

    // copy all alphabetic characters into new string
    char result[50];

    for (int i = 0, j = 0; i < strlen(name1); i++) {
        // check if alphabet
        if (isalpha(name1[i])) {
            result[j] = name1[i];
            j++;
        }
    }

    for (int i = 0, j = strlen(result); i < strlen(name2); i++) {
        // check if alphabet
        if (isalpha(name2[i])) {
            result[j] = name2[i];
            j++;
        }
    }

    printf("Remaining character count: %i\n", strlen(result));
}

void freeStringArray(char **mat, int n) {
    for (int i = 0; i < n; i++) {
        free(mat[i]);
    }

    free(mat);
}
