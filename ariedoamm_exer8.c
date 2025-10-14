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
    int num_of_bought_items;
};

// function declarations
int menu();
void addItem(struct Item* items, int *);
void buyItem(struct Item* items, struct Buyer* buyers, int *, int *);
void editItem(struct Item* items, int *);
void deleteItem(struct Item* items, int *);
void viewItems(struct Item* items, int *);
void viewBuyers(struct Buyer* buyers, int *);
void save(struct Item* items, struct Buyer* buyers, int *, int *);
void load(struct Item* items, struct Buyer* buyers);
void findItem(struct Item* items, char *name, struct Item *item_found, int *);

int main() {
    // arrays for items and buyers
    struct Item *items;
    struct Buyer *buyers;
    items = (struct Item *) malloc(10 * sizeof(struct Item));
    buyers = (struct Buyer *) malloc(10 * sizeof(struct Buyer));

    int item_count = 0;
    int buyer_count = 0;

    // load any saved file
    //load(items, buyers);

    int choice = 0; // for user input

    do { // loop until user chooses to exit
        choice = menu();

        switch (choice)
        {
        case 1:
            addItem(items, &item_count);
            break;
            
        case 2:
            buyItem(items, buyers, &item_count, &buyer_count);
            break;
            
        case 3:
            editItem(items, &item_count);
            break;
            
        case 4:
            deleteItem(items, &item_count);
            break;
            
        case 5:
            viewItems(items, &item_count);
            break;
            
        case 6:
            viewBuyers(buyers, &buyer_count);
            break;
            
        case 7:
            save(items, buyers, &item_count, &buyer_count);
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
    scanf("%d%*c", &choice);

    return choice;
}

// add item to array of items
void addItem(struct Item* items, int *item_count) {
    // check if there is still available item space
    if (*item_count >= 10) {
        printf("\nCannot add any more items!\n\n");
        return;
    }

    // initialization
    char item_name[50];
    int price = 0;
    int stock = 0;

    // user inputs
    printf("\nEnter item name: ");
    scanf("%[^\n]%*c", item_name);

    printf("Enter price: ");
    scanf("%d", &price);

    printf("Enter stock: ");
    scanf("%d", &stock);
    printf("\n");

    // iterate over items array
    // check if item already exists
    for (int i = 0; i < 10; i++) {
        if (strcmp(items[i].name, item_name) == 0) {
            printf("Item already exists!\n\n");
            return;
        }
    }

    // no duplicate item and there is still available space
    strcpy(items[*item_count].name, item_name);
    items[*item_count].price = price;
    items[*item_count].stock = stock;
    (*item_count)++;
}  

// have a buyer buy an item
void buyItem(struct Item* items, struct Buyer* buyers, int *item_count, int *buyer_count) {
    // check if there are items to buy
    if (*item_count == 0) {
        printf("\nThere are no grocery items available!\n\n");
        return;
    }

    // user enters customer name
    char buyer_name[50];
    printf("\nEnter customer name: ");
    scanf("%[^\n]%*c", buyer_name);

    // check for existing buyer 
    int index;
    for (index = 0; index < *buyer_count; index++) {

        // found existing buyer
        if (strcmp(buyer_name, buyers[index].name) == 0) break;
    }

    // check if there are still enough buyers to remember
    if (index == 10) {
        printf("\nThere are already too many buyers!\n");
        return;
    }

    // initialize item bought count for new buyers
    if (index == *buyer_count) buyers[index].num_of_bought_items = 0;

    // check if buyer can still buy more items
    if (buyers[index].num_of_bought_items == 5){
        printf("\n%s cannot buy any more items!\n", buyers[index].name);
        return;
    }

    // print existing items
    printf("\n----------GROCERY ITEMSS AVAILABLE----------\n");
    for (int i = 0; i < *item_count; i++) {
        printf("[%i] %s - %i\n", i+1, items[i].name, items[i].price);
    }

    // user chooses item to buy
    int choice = 0;
    printf("Enter grocery item to buy: ");
    scanf("%i", &choice);

    // check if valid input
    if (choice > *item_count || choice < 1) {
        printf("\nGrocery item not found!\n");
        return;
    }
    printf("%iaaaa\n", choice);

    // check if enough stock
    if (items[choice-1].stock == 0) {
        printf("\n%s is out of stock!\n", items[choice-1].name);
        return;
    }
    printf("%ibbb\n", choice);

    // update buyer
    strcpy(buyers[index].name, buyer_name);
    buyers[index].bought_items[ buyers[index].num_of_bought_items ] = items[choice-1];
    buyers[index].total_cost += items[choice-1].price;
    buyers[index].num_of_bought_items++;
}

// edit an existing item
void editItem(struct Item* items, int *item_count) {

}

// delete an existing item
void deleteItem(struct Item* items, int *item_count) {

}

// print all items
void viewItems(struct Item* items, int *item_count) {
    if (*item_count == 0) {
        printf("\nThere are current no grocery items.\n");
        return;
    }

    // iterate over item array
    for (int i = 0; i < *item_count; i++) {
        printf("\nGrocery Item: %s\n", items[i].name);
        printf("Item Price: %d\n", items[i].price);
        printf("Stock: %d\n", items[i].stock);
    }
}

// print all buyers
void viewBuyers(struct Buyer* buyers, int *buyer_count) {
    printf("\n");

    // iterate over array of buyers
    for (int i = 0; i < *buyer_count; i++) {
        printf("Customer Name: %s\n", buyers[i].name);
        printf("Grocery Items bought:\n");

        // iterate over all items bought by buyer
        for (int j = 0; j < buyers[i].num_of_bought_items; j++) {
            printf(" - %s\n", buyers[i].bought_items[j].name);
        }

        printf("Total Cost: %i\n", buyers[i].total_cost);
    }
}

// save items and buyers
void save(struct Item* items, struct Buyer* buyers, int *item_count, int *buyer_count) {

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
    int item_count = 0;
    struct Item *item; // buffer

    // populate Items array
    for (int i = 0; i < 10; i++) {
        item = &items[i];
        check = fscanf(fptr, "%s,%d,%d", item->name, &(item->price), &(item->stock));
        item_count++;

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
    char item_name[50];
    check = 0;

    // populate Buyers array
    for (int i = 0; i < 10; i++) {
        buyer = &(buyers[i]);
        check = fscanf(fptr, "%s,%d,%d", buyer->name, &(buyer->num_of_bought_items), &(buyer->total_cost));

        // end of file
        if (check == 0) break;

        // get the items bought
        for (int j = 0; j < (buyer->num_of_bought_items); j++) {
            fscanf(fptr, "%s", item_name);
            findItem(items, item_name, &(buyer->bought_items[j]), &item_count);
        }
    }

    fclose(fptr);
}

void findItem(struct Item* items, char *name, struct Item *item_found, int *item_count) {

}

