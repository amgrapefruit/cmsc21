/**
 * Author: Aaron Michael M. Ariedo
 * Date: 14 october 2025
 * CMSC 21: Exercise 8
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// grocery item structure
struct Item {
    char name[50];
    int price;
    int stock;
};

// buyer structure
struct Buyer {
    char name[50];
    struct Item bought_items[5];
    int total_cost;
};

// function declarations
int menu();
void addItem(struct Item* items);
void buyItem(struct Item* items, struct Buyer* buyers);
void editItem(struct Item* items);
void deleteItem(struct Item* items);
void viewItems(struct Item* items);
void viewBuyers(struct Buyer* buyers);
void save(struct Item* items, struct Buyer* buyers);
void load(struct Item* items, struct Buyer* buyers);
int isItemsEmpty(struct Item* items);
int isBuyersEmpty(struct Buyer* buyers);
void findItem(struct Item* items, char *name, struct Item *item_found);

int main() {
    // arrays for items and buyers
    struct Item *items;
    struct Buyer *buyers;
    items = (struct Item *) malloc(10 * sizeof(struct Item));
    buyers = (struct Buyer *) malloc(10 * sizeof(struct Buyer));

    // load any saved file
    load(items, buyers);

    int choice = 0; // for user input

    do { // loop until user chooses to exit
        choice = menu();

        for (int i = 0; i < 10; i++) {
            printf("%s, %s &d\n", items[i], buyers[i], choice);
        }

        switch (choice)
        {
        case 1:
            break;
            
        case 2:
            break;
            
        case 3:
            break;
            
        case 4:
            break;
            
        case 5:
            break;
            
        case 6:
            break;
            
        case 7:
            break;
        
        default:
            break;
        }

    } while (choice != 7);

    printf("You have exited.\n");

    return 0;
}

int menu() {
    // print menu
    printf("==================MENU==================\n");
    printf("[1] Add Grocery Item\n");
    printf("[2] Buy Grocery Item\n");
    printf("[3] Edit Grocery Item\n");
    printf("[4] Delete Grocery Item\n");
    printf("[5] View All Grocery Items\n");
    printf("[6] View All Buyers\n");
    printf("[7] Exit\n");

    // ask for user input
    printf("\nEnter choice: ");
    int choice = 0;
    scanf("%d", &choice);

    return choice;
}

// add item to array of items
void addItem(struct Item* items) {

}

// have a buyer buy an item
void buyItem(struct Item* items, struct Buyer* buyers) {

}

// edit an existing item
void editItem(struct Item* items) {

}

// delete an existing item
void deleteItem(struct Item* items) {

}

// print all items
void viewItems(struct Item* items) {

}

// print all buyers
void viewBuyers(struct Buyer* buyers) {

}

// save items and buyers
void save(struct Item* items, struct Buyer* buyers) {

}

// load items and buyers
void load(struct Item* items, struct Buyer* buyers) {
    FILE* fptr = fopen("items.txt", "r");

    // check if file is found
    if (fptr == NULL) {
        printf("Found no save file");
        return;
    }

    int check = 0;
    struct Item *item; // buffer

    // populate Items array
    for (int i = 0; i < 10; i++) {
        item = &items[i];
        check = fscanf(fptr, "%s,%d,%d", item->name, &(item->price), &(item->stock));

        // end of file
        if (check == 0) break;
    }

    fclose(fptr);

    fopen("buyers.txt", "r");

    // check if file is found
    if (fptr == NULL) {
        printf("Found no save file");
        return;
    }

    struct Buyer *buyer; // buffer
    int item_count = 0;
    char item_name[50];
    check = 0;

    // populate Buyers array
    for (int i = 0; i < 10; i++) {
        buyer = &(buyers[i]);
        check = fscanf(fptr, "%s,%d,%d", buyer->name, &item_count, &(buyer->total_cost));

        // end of file
        if (check == 0) break;

        // get the items bought
        for (int j = 0; j < item_count; j++) {
            fscanf(fptr, "%s", item_name);
            findItem(items, item_name, &(buyer->bought_items[j]));
        }
    }

    fclose(fptr);
}

int isItemsEmpty(struct Item* items) {

}

int isBuyersEmpty(struct Buyer* buyers) {

}

void findItem(struct Item* items, char *name, struct Item *item_found) {

}

