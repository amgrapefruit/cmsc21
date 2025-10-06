/**
 * Author: Aaron Michael M. Ariedo
 * Date: 14 September 2025
 * CMSC 21: Exercise 2
 */

#include <stdio.h>
#include <math.h>

int menu();
int check_pin(int pin);
int check_balance(int pin, float balance);
float deposit(int pin, float balance);
float withdraw(int pin, float balance);
int change_pin(int pin);

int main() {

    int choice = 0;
    int pin = 1234;
    float balance = 0;

    // main loop
    while (1) {
        choice = menu();

        if (choice == 1){
            // user chose to check balance
            check_balance(pin, balance);
        }
        else if (choice == 2) {
            // user chose to deposit
            balance = deposit(pin, balance);
        }
        else if (choice == 3) {
            // user chose to withdraw
            balance = withdraw(pin, balance);
        }
        else if (choice == 4) {
            // user chose to change pin
            pin = change_pin(pin);
        }
        else if (choice == 5) {
            break; // end loop and exit
        }
        else { // input is outside of choices
            printf("Invalid input!\n");
        }
    
    }

    return 0; // end program
}

int menu(){

    // print texts
    printf("*********************\n");
    printf("WELCOME TO MAZE BANK!\n");
    printf("*********************\n");
    printf("[1] Check Balance\n");
    printf("[2] Deposit\n");
    printf("[3] Withdraw\n");
    printf("[4] Change PIN\n");
    printf("[5] End Transaction\n");
    printf("Enter choice: ");
    
    // get user choice and return
    int choice = 0;
    scanf("%i", &choice);

    return choice;
}

int check_pin(int pin) {

    // loop to iteratively ask and check input pin
    while (1) {

        // user inputs pin
        printf("Please enter your 4-digit PIN: ");
        int input = 0;
        scanf("%i", &input);

        // compare pins
        if (pin == input) {
            return 1; // success and quit function
        }

        // unsuccessful and try again
        printf("You entered an incorrect PIN. Please try again.\n");
    }

}

int check_balance(int pin, float balance){

    // check for correct pin input
    check_pin(pin);

    // display balance
    printf("Current Balance: %.0f\n\n", roundf(balance*100)/100);

    return 1;
} 

float deposit(int pin, float balance) {
    float deposit = 0;
    float new_balance = balance;

    // check for correct pin input
    check_pin(pin);

    // display current balance
    printf("Current Balance: %.0f\n", roundf(balance*100)/100);

    // ask for depost
    printf("Deposit Amount: ");
    scanf("%f", &deposit);
    new_balance += deposit;

    // display new balance
    printf("Updated Balance: %.0f\n\n", roundf(new_balance*100)/100);

    return new_balance;
}

float withdraw(int pin, float balance) {
    float withdrawal = 0;
    float new_balance = balance;

    // check for correct pin input
    check_pin(pin);

    // display current balance
    printf("Current Balance: %.0f\n", roundf(balance*100)/100);

    // ask for depost
    printf("Withdrawal Amount: ");
    scanf("%f", &withdrawal);

    // check if sufficient balance
    if (balance < withdrawal) {

        // insufficient balance
        printf("Insufficient Balance!\n\n");

        // new balance is left equal to unchanged balance
    }
    else {

        // display new balance
        new_balance -= withdrawal;
        printf("Updated Balance: %.0f\n\n", roundf(new_balance*100)/100);
    }

    return new_balance;
}

int change_pin(int pin) {
    int new_pin = 0;

    // check for correct pin input
    check_pin(pin);

    // ask for new pin
    printf("Please enter your new 4-digit PIN: ");
    scanf("%i", &new_pin);

    // checks if pin has 4 digits
    if (new_pin > 999 && new_pin < 10000) {

        // pin has 4 digits
        printf("PIN successfully changed!\n\n");
        return new_pin;
    }
    else {

        // pin does not have 4 digits
        printf("Invalid PIN!\n\n");
        return pin;
    }
}