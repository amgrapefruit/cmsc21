/**
 * Author: Aaron Michael M. Ariedo
 * Date: 4 November 2025
 * CMSC 21: Exercise 10
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Used to create an instance of a grocery item
typedef struct groceryItems_tag {
    char item_name[30];
    float price;
    int stock;
    struct groceryItems_tag *nextItem;
} groceryItems;


// Used to create a booking linked list for each customer. This is so that you
// can access the details of the specific event in the event linked list
struct cart {
    struct groceryItems_tag *item_bought;
    struct cart *nextItem;
};

//Used to create an instance of a buyer
typedef struct buyer_tag {
    char name[30];
    struct buyer_tag *nextBuyer;
    struct cart *groceryItemsBought;
    float total_cost;
} buyer;

// function declarations
int menu();
void addItem(groceryItems **grocery_head);
void viewItems(groceryItems **grocery_head);

int main() {

    // for user input
    int choice = 0;

    // heads for each node_tag
    groceryItems *grocery_head = NULL;
    buyer *buyers_head = NULL;

    do { // repeat program until user exits
        choice = menu();

        switch (choice)
        {
        case 1:
            addItem(&grocery_head);
            break;

        case 2:
            
            break;

        case 3:
            break;

        case 4:
            
            break;
            
        case 5:
            viewItems(&grocery_head);
            break;
            
        case 6:
            
            break;
            
        case 7:
            
            break;
        
        default: // user inputs invalid integer choice
            printf("Please input a valid choice.\n");    

            break;
        }
    } while (choice != 7);

}

// print menu and get user input
int menu() {
    int choice = 0;

    // print menu
    printf("=========== MENU ===========\n");
    printf("[1] Add Grocery Item\n");
    printf("[2] Buy Grocery Item\n");
    printf("[3] Edit Grocery Item\n");
    printf("[4] Delete Grocery Item\n");
    printf("[5] View All Grocery Items\n");
    printf("[6] View All Buyers\n");
    printf("[7] Exit\n");

    printf("\nEnter choice: ");
    scanf("%i", &choice);

    return choice;
}

// add unique grocery item, arranged alphabetically
void addItem(groceryItems **head) {

    // ask user for item details
    char item_name[30];
    float price;
    int stock;

    printf("\nEnter item name: ");
    scanf("%s", item_name);
    printf("Enter price: ");
    scanf("%f", &price);
    printf("Enter stock: ");
    scanf("%i", &stock);

    // declare and initialize new_node
    groceryItems *new_item = (groceryItems *) malloc(sizeof(groceryItems));
    strcpy(new_item->item_name, item_name);
    new_item->price = price;
    new_item->stock = stock;
    new_item->nextItem = NULL;

    // check if item is not first
    if (*head != NULL) {
            
        // item is before head
        if (strcmp(item_name, (*head)->item_name) < 0) {

            // insert at head
            new_item->nextItem = (*head); 
            *head = new_item;
        }

        else {

            // iterate until correct alphabetical place
            groceryItems *prev = *head;
            groceryItems *curr;

            while (prev->nextItem != NULL) { // iterate until last node

                // go next and compare item_name with names of prev and curr item
                curr = prev->nextItem;
                
                // item already exists
                if (strcmp(item_name, curr->item_name) == 0 || strcmp(item_name, prev->item_name) == 0) {

                    printf("\nGrocery item already exists!\n");
                    return;
                } 

                // item is before curr after prev
                else if (strcmp(item_name, curr->item_name) < 0) {

                    // insert between prev and curr
                    new_item->nextItem = curr;
                    prev->nextItem = new_item;
                    break;
                }

                prev = prev->nextItem; // traverse linked list
            }

            // new item, alphabetically last
            prev->nextItem = new_item;
        }
        
    } else { // first item

        // declare and initialize first node
        *head = new_item;
    }

    printf("\nSuccessfully added item!\n");
}

// print all grocery items
void viewItems(groceryItems **head) {

    // check if no item exists
    if (*head == NULL) {
        printf("\nThere are no grocery items available!\n");
        return;
    }

    // traverse linked list
    groceryItems *ptr = *head;

    while (ptr != NULL) {
        printf("\nGrocery Item: %s\n", ptr->item_name);
        printf("Item Price: %.2f\n", ptr->price);
        printf("Stock: %i\n", ptr->stock);

        ptr = ptr->nextItem;
    }
}