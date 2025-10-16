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
void load(struct Item* items, struct Buyer* buyers, int *, int *);
void findItem(struct Item* items, char *name, struct Item **item_found, int *);

int main() {
    // arrays for items and buyers
    struct Item *items;
    struct Buyer *buyers;
    items = (struct Item *) malloc(10 * sizeof(struct Item));
    buyers = (struct Buyer *) malloc(10 * sizeof(struct Buyer));

    int item_count = 0;
    int buyer_count = 0;

    // load any saved file
    load(items, buyers, &item_count, &buyer_count);

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
        
        default:
            break;
        }

    } while (choice != 7);

    printf("You have exited.\n");
    save(items, buyers, &item_count, &buyer_count);

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

    // check if item already exists
    struct Item *item; // item pointer
    findItem(items, item_name, &item, item_count);
    if (item != NULL) {
        printf("\nGrocery item already exists!\n");
        return;
    }

    printf("Enter price: ");
    scanf("%d", &price);

    printf("Enter stock: ");
    scanf("%d", &stock);
    printf("\n");

    // no duplicate item and there is still available space
    // add item to array
    strcpy(items[*item_count].name, item_name);
    items[*item_count].price = price;
    items[*item_count].stock = stock;
    (*item_count)++;

    printf("Successfully added grocery item!\n");
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

    // check if enough stock
    if (items[choice-1].stock == 0) {
        printf("\n%s is out of stock!\n", items[choice-1].name);
        return;
    }


    // initialize new buyers
    if (index == *buyer_count) {
        buyers[index].num_of_bought_items = 0;
        buyers[index].total_cost = 0;
        (*buyer_count)++;
    }

    // update buyer
    strcpy(buyers[index].name, buyer_name);
    buyers[index].bought_items[ buyers[index].num_of_bought_items ] = items[choice-1];
    buyers[index].total_cost += items[choice-1].price;
    buyers[index].num_of_bought_items += 1;

    items[choice-1].stock--; // decrement stock

    printf("\nSuccessfully bought grocery item: %s!\n", items[choice-1].name);
}

// edit an existing item
void editItem(struct Item* items, int *item_count) {
    
    // ask user for item name
    printf("\nEnter grocery item name: ");
    char item_name[50];
    scanf("%[^\n]%*c", item_name);

    // find item that matches
    struct Item *item; // item pointer
    findItem(items, item_name, &item, item_count);

    // check if item not found
    if (item == NULL) {
        printf("\nItem was not found!\n");
        return;
    }

    // item was found
    // ask for new item details
    int price = 0;
    int stock = 0;

    printf("Enter new price: ");
    scanf("%i", &price);

    printf("Enter new stock: ");
    scanf("%i", &stock);

    // update item
    item->price = price;
    item->stock = stock;

    printf("\nGrocery Item Details Successfully Edited!\n");
}

// delete an existing item
void deleteItem(struct Item* items, int *item_count) {
    
    // ask user for item name
    printf("\nEnter grocery item name: ");
    char item_name[50];
    scanf("%[^\n]%*c", item_name);

    // find item that matches
    struct Item *item; // item pointer
    findItem(items, item_name, &item, item_count);

    // check if item not found
    if (item == NULL) {
        printf("\nItem was not found!\n");
        return;
    }

    // item was found
    // iterate over items array
    int j = 0;
    for (int i = j; i < *item_count; i++) {

        // copy all items onto item array again except item to be deleted
        if (strcmp(items[i].name, item_name) != 0) {
            items[j++] = items[i];
        }
    }

    (*item_count)--;

    printf("\nSuccessfully deleted an item!\n");
}

// print all items
void viewItems(struct Item* items, int *item_count) {
    if (*item_count == 0) {
        printf("\nThere are currently no grocery items.\n");
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
    // check if there are any buyers
    if (*buyer_count == 0) {
        printf("\nThere are no buyers yet!\n");
    }

    // iterate over array of buyers
    for (int i = 0; i < *buyer_count; i++) {
        printf("\nCustomer Name: %s\n", buyers[i].name);
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

    // check if there is data to be saved
    if (*item_count == 0 && *buyer_count == 0) {
        printf("\nThere is no data that can be saved\n");
    }

    // save items
    FILE *items_fptr = fopen("items.txt", "w");

    // iterate over items array
    for (int i = 0; i < *item_count; i++) {
        // write each item to save file
        fprintf(items_fptr, "%s,%d,%d\n", items[i].name, items[i].price, items[i].stock);
    }

    fclose(items_fptr);

    // save buyers
    FILE *buyers_fptr = fopen("buyers.txt", "w");

    // iterate over items array
    for (int i = 0; i < *buyer_count; i++) {
        // write each buyer to save file
        fprintf(buyers_fptr, "%s,%d,%d\n", buyers[i].name, buyers[i].num_of_bought_items, buyers[i].total_cost);

        // write each item bought to save file
        for (int j = 0; j < buyers[i].num_of_bought_items; j++) {
            fprintf(buyers_fptr, "%s\n", buyers[i].bought_items[j].name);
        }
    }

    fclose(buyers_fptr);
}

// load items and buyers
void load(struct Item* items, struct Buyer* buyers, int *item_count, int *buyer_count) {
    FILE* items_fptr = fopen("items.txt", "r");

    // check if file is found
    if (items_fptr == NULL) {
        printf("Found no save file");
        return;
    }

    // buffers for item fields
    char item_name[50];
    int item_price = 0;
    int item_stock = 0;
    int item_index = 0;

    // populate Items array
    while (fscanf(items_fptr, "%s,%d,%d", item_name, item_price, item_stock) > 0) {
        
        // copy all fields
        strcpy(items[item_index].name, item_name);
        items[item_index].price = item_price;
        items[item_index].stock = item_stock;
        item_index++;
    }
    

    fclose(items_fptr);

    FILE *buyers_fptr = fopen("buyers.txt", "r");

    // check if file is found
    if (buyers_fptr == NULL) {
        printf("Found no save file");
        return;
    }

    // buffers for items and buyers
    char buyer_name[50];
    int buyer_num_of_bought_items = 0;
    int buyer_total_cost = 0;
    int buyer_index = 0;

    strcpy(item_name, "");
    struct Item *item;

    int check = 0;

    // populate Buyers array
    while (fscanf(buyers_fptr, "%s,%d,%d", buyer_name, buyer_num_of_bought_items, buyer_total_cost) > 0){

        // copy buyer fields
        strcpy(buyers[buyer_index].name, buyer_name);
        buyers[buyer_index].num_of_bought_items = buyer_num_of_bought_items;
        buyers[buyer_index].total_cost = buyer_total_cost;

        // copy items bought
        for (int i = 0; i < buyer_num_of_bought_items; i++) {
            fscanf(buyers_fptr, "%s", item_name);
            findItem(items, item_name, &item, item_count);

            buyers[buyer_index].bought_items[i] = *item;
        }

        buyer_index++;
    }

    // update array sizes
    *item_count = item_index;
    *buyer_count = buyer_index;

    fclose(buyers_fptr);
}
/*
    for (int i = 0; i < 10; i++) {
        buyer = &(buyers[i]);
        check = fscanf(buyers_fptr, "%s,%d,%d", buyer->name, &(buyer->num_of_bought_items), &(buyer->total_cost));

        // end of file
        if (check == 0) break;

        // get the items bought
        for (int j = 0; j < (buyer->num_of_bought_items); j++) {
            fscanf(buyers_fptr, "%s", item_name);
            findItem(items, item_name, &buyer_item, item_count);
            
            // add item to buyer's item list
            buyer->bought_items[j] = *buyer_item;
        }

        (*buyer_count)++;
    }

    fclose(buyers_fptr);
}
*/
// find item from items array, pass-by reference
void findItem(struct Item* items, char *name, struct Item **item_found, int *item_count) {
    
    // iterate over all arrays
    for (int i = 0; i < *item_count; i++) {
        
        // item name matches
        if (strcmp(name, items[i].name) == 0) {
            *item_found = &(items[i]);
            return;
        }
    }

    // no match was found
    *item_found = NULL;
    return;
}

