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
void viewItems(groceryItems *grocery_head);
void buyItem(buyer **buyers_head, groceryItems *grocery_head);
void viewBuyers(buyer *buyers_head);
void editItem(groceryItems *grocery_head);
groceryItems* findInCart(buyer *buyer, groceryItems *item);
void deleteItem(groceryItems **grocery_head, buyer *buyer_head);
void save(groceryItems *grocery_head, buyer *buyers_head);
void load(groceryItems **grocery_head, buyer **buyers_head);

int main() {

    // for user input
    int choice = 0;

    // heads for each node_tag
    groceryItems *grocery_head = NULL;
    buyer *buyers_head = NULL;

    //load(&grocery_head, &buyers_head);

    do { // repeat program until user exits
        choice = menu();

        switch (choice)
        {
        case 1:
            addItem(&grocery_head);
            break;

        case 2:
            buyItem(&buyers_head, grocery_head);
            break;

        case 3:
            editItem(grocery_head);
            break;

        case 4:
            deleteItem(&grocery_head, buyers_head);
            break;
            
        case 5:
            viewItems(grocery_head);
            break;
            
        case 6:
            viewBuyers(buyers_head);
            break;
            
        case 7:
            save(grocery_head, buyers_head);
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
    scanf("%d%*c", &choice);

    return choice;
}

// add unique grocery item, arranged alphabetically
void addItem(groceryItems **head) {

    // ask user for item details
    char item_name[30];
    float price = 0;
    int stock = 0;

    printf("\nEnter item name: ");
    scanf("%[^\n]%*c", item_name);

    // declare and initialize new_node
    groceryItems *new_item = (groceryItems *) malloc(sizeof(groceryItems));
    strcpy(new_item->item_name, item_name);
    new_item->price = price;
    new_item->stock = stock;
    new_item->nextItem = NULL;

    // check if item already exists
    // first item added
    if (*head == NULL) {
        *head = new_item;
    }
    
    else {
            
        // item is before head
        if (strcmp(item_name, (*head)->item_name) < 0) {

            // insert at head
            new_item->nextItem = (*head); 
            *head = new_item;
        }

        // item is head
        else if (strcmp(item_name, (*head)->item_name) == 0) {

            printf("\nGrocery item already exists!\n");
            return;
        }

        // item is after head
        else {

            // iterate until correct alphabetical place
            groceryItems *prev = *head;
            groceryItems *curr = prev->nextItem;

            while (curr != NULL) { // iterate until last node
                
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

                // go next and compare item_name with names of prev and curr item
                prev = curr;
                curr = curr->nextItem;
            }

            // new item, alphabetically last
            prev->nextItem = new_item;
        }
        

    }

    // update item stock and price
    printf("Enter price: ");
    scanf("%f", &(new_item->price));
    printf("Enter stock: ");
    scanf("%i", &(new_item->stock));

    printf("\nSuccessfully added item!\n");
}

// print all grocery items
void viewItems(groceryItems *head) {

    // check if no item exists
    if (head == NULL) {
        printf("\nThere are no grocery items available!\n");
        return;
    }

    // traverse linked list
    groceryItems *ptr = head;

    while (ptr != NULL) {
        printf("\nGrocery Item: %s\n", ptr->item_name);
        printf("Item Price: %.2f\n", ptr->price);
        printf("Stock: %i\n", ptr->stock);

        ptr = ptr->nextItem;
    }
}

// have a buyer buy a grocery item
void buyItem(buyer **buyers_head, groceryItems *grocery_head) {

    if (grocery_head == NULL) {
        printf("\nThere are no grocery items available!\n");
        return;
    }

    // ask user for buyer name
    char name[30];
    printf("\nEnter customer name: ");
    scanf("%[^\n]%*c", name);

    // display item choices
    printf("\n-------- GROCERY ITEMS AVAILABLE --------\n");

    // traverse grocery items linked list
    groceryItems *item_ptr = grocery_head;
    for (int i = 1; item_ptr != NULL; i++) {

        // display item details
        printf("[%i] %s - %.2f\n", i, item_ptr->item_name, item_ptr->price);

        // go next
        item_ptr = item_ptr->nextItem;
    }

    // ask user item choice
    int choice = 0;
    printf("\nEnter grocery item to buy: ");
    scanf("%i", &choice);

    // check if item exists
    int found = 0;
    item_ptr = grocery_head;
    for (int i = 1; item_ptr != NULL; i++) {

        // check for match
        if (choice == i) {

            // item out of stock
            if (item_ptr->stock == 0) {
                printf("\n%s is out of stock!\n", item_ptr->item_name);
                return;
            }

            item_ptr->stock--;

            found = 1;
            break;
        }

        // go next
        item_ptr = item_ptr->nextItem;
    }

    // item not found
    if (found == 0) {
        printf("\nGrocery item not found!\n");
        return;
    }

    // initialize new buyer
    buyer *new_buyer;
    new_buyer = (buyer *) malloc(sizeof(buyer));
    strcpy(new_buyer->name, name);
    new_buyer->total_cost = item_ptr->price;
    new_buyer->nextBuyer = NULL;
    
    struct cart *new_cart = (struct cart*) malloc(sizeof(struct cart));
    new_cart->item_bought = item_ptr;
    new_cart->nextItem = NULL;
    new_buyer->groceryItemsBought = new_cart;
    
    // first buyer
    if (*buyers_head == NULL) {
        *buyers_head = new_buyer;
    }
    
    // existing / new buyer
    else {

        // traverse buyer linked list
        buyer *buyer_ptr = *buyers_head;

        while (buyer_ptr != NULL) {

            // buyer already exists
            if (strcmp(buyer_ptr->name, name) == 0) {

                // update existing buyer
                buyer_ptr->total_cost += new_buyer->total_cost;

                // traverse to end of cart linked link
                struct cart *cart_ptr = buyer_ptr->groceryItemsBought;

                while (cart_ptr->nextItem != NULL) {
                    cart_ptr = cart_ptr->nextItem;
                }

                // add to buyer cart
                cart_ptr->nextItem = new_buyer->groceryItemsBought;

                break;
            }

            // new buyer
            if (buyer_ptr->nextBuyer == NULL) {
                buyer_ptr->nextBuyer = new_buyer;
                break;
            }

            buyer_ptr = buyer_ptr->nextBuyer;
        } 

    }
    
    printf("\nSuccessfully bought grocery item: %s\n", item_ptr->item_name);
}

// print out all buyers and their bought items
void viewBuyers(buyer *head) {

    // check if no buyer exists
    if (head == NULL) {
        printf("\nThere are no buyers yet!\n");
        return;
    }

    // traverse buyers linked list
    buyer *buyer_ptr = head;
    struct cart *cart_ptr;

    while (buyer_ptr != NULL) {

        // print buyer details
        printf("\nCustomer Name: %s\n", buyer_ptr->name);
        printf("Grocery Items bought:\n");

        // traverse cart linked list
        cart_ptr =  buyer_ptr->groceryItemsBought;

        while (cart_ptr != NULL) {

            // print buyer cart
            printf(" - %s\n", cart_ptr->item_bought->item_name);
            
            cart_ptr = cart_ptr->nextItem;
        }
        
        buyer_ptr = buyer_ptr->nextBuyer;
    }

}

// edit an existing grocery item
void editItem(groceryItems *head) {

    // empty grocery item linked list
    if (head == NULL) {
        printf("\nThere are no grocery items yet!\n");
        return;
    }

    // ask user for item name
    printf("\nEnter grocery item name: ");
    char name[30];
    scanf("%[^\n]%*c", name);

    // find existing item
    groceryItems *item_ptr = head;

    while(item_ptr != NULL) {

        // found match
        if (strcmp(item_ptr->item_name, name) == 0) break;

        item_ptr = item_ptr->nextItem;
    }

    // no match found
    if (item_ptr == NULL) {
        printf("\nItem does not exist!\n");
        return;
    }

    // update item details
    float new_price;
    int new_stock;

    printf("Enter new price: ");
    scanf("%f", &new_price);
    printf("Enter new stock: ");
    scanf("%i", &new_stock);

    item_ptr->price = new_price;
    item_ptr->stock = new_stock;

    printf("\nSuccessfully edited grocery item details!\n");
}

// find item in buyer cart
groceryItems* findInCart(buyer *buyer, groceryItems *item) {

    // declare and initialize cart pointer
    struct cart *cart_ptr = (struct cart *) malloc(sizeof(struct cart));
    cart_ptr = buyer->groceryItemsBought;

    // traverse buyer cart
    while (cart_ptr != NULL) {

        // found item
        if (cart_ptr->item_bought == item) {
            return item;
        }

        // traverse
        cart_ptr = cart_ptr->nextItem;
    }

    // item not found
    return NULL;
}

// delete an existing grocery item
void deleteItem(groceryItems **head, buyer *buyers_head) {

    // empty grocery item linked list
    if (head == NULL) {
        printf("\nThere are no grocery items yet!\n");
        return;
    }

    // ask user for item
    printf("\nEnter grocery item name: ");
    char name[30];
    scanf("%[^\n]%*c", name);

    // for check if buyer has bought the item
    buyer *buyer_ptr = buyers_head;

    // find existing item
    groceryItems *item_ptr = *head;

    // delete head
    if (strcmp((*head)->item_name, name) == 0) {

        // traverse buyers
        while (buyer_ptr != NULL) {

            // check if item is in buyer cart
            if (findInCart(buyer_ptr, item_ptr) != NULL) {
                printf("\nBought item cannot be deleted!\n");
                return;
            }

            buyer_ptr = buyer_ptr->nextBuyer;
        }

        *head = (*head)->nextItem;
        free(item_ptr);
    }

    else {
        // traverse linked list
        groceryItems *prev = item_ptr;
        item_ptr = item_ptr->nextItem;

        while (item_ptr != NULL) {

            // found item to be deleted
            if (strcmp(item_ptr->item_name, name) == 0) {
                
                // traverse buyers
                while (buyer_ptr != NULL) {
                    
                    // check if item is in buyer cart
                    if (findInCart(buyer_ptr, item_ptr) != NULL) {
                        
                        printf("\nBought item cannot be deleted!\n");
                        return;
                    }
                    
                    buyer_ptr = buyer_ptr->nextBuyer;
                }

                prev->nextItem = item_ptr->nextItem;
                free(item_ptr);
                break;
            }
            
            // not found, go next
            prev = item_ptr;
            item_ptr = item_ptr->nextItem;
        }
    }

    // no match found
    if (item_ptr == NULL) {
        printf("\nItem does not exist!\n");
        return;
    }

    printf("\nSuccessfully deleted item!\n");
}

// save buyers and grocery items in file
void save(groceryItems *grocery_head, buyer *buyers_head) {

}

// load buyers and grocery items from file
void load(groceryItems **grocery_head, buyer **buyers_head) {
    
    // load items
    FILE* items_fptr = fopen("items.txt", "r");

    // check if file is found
    if (items_fptr == NULL) {
        printf("Found no save file");
        return;
    }

    // buffers for item fields
    char item_name[30];
    int item_price = 0;
    int item_stock = 0;

    // pointers for traversing
    groceryItems *grocery_tail = (groceryItems *) malloc(sizeof(groceryItems));

    // read lines in file
    while (fscanf(items_fptr, "%s %d %d", item_name, &item_price, &item_stock) > 0) {

        // new item
        groceryItems *new_item = (groceryItems *) malloc(sizeof(groceryItems));
        strcpy(new_item->item_name, item_name);
        new_item->price = item_price;
        new_item->stock = item_stock;
        new_item->nextItem = NULL;

        // head item
        if (*grocery_head == NULL) {
            
            // head points at new item
            *grocery_head = new_item;
        }

        // item after head
        else {

            // add new_item to tail
            grocery_tail->nextItem = new_item;
        }

        // traverse
        grocery_tail = new_item;
        
    }

    fclose(items_fptr);

    // load buyers
    FILE *buyers_fptr = fopen("buyers.txt", "r");

    // check if file is found
    if (buyers_fptr == NULL) {
        printf("Found no save file");
        return;
    }

    // buffers for items and buyers
    char buyer_name[30];
    int buyer_num_of_bought_items = 0;
    int buyer_total_cost = 0;

    // bought item uninitialized
    strcpy(item_name, "");
    groceryItems *bought_item = *grocery_head;

    // read file per line
    while (fscanf(buyers_fptr, "%s %d %d", buyer_name, &buyer_num_of_bought_items, &buyer_total_cost) > 0) {

        // new buyer
        buyer *new_buyer = (buyer *) malloc(sizeof(buyer));
        strcpy(new_buyer->name, buyer_name);
        new_buyer->total_cost = buyer_total_cost;

        // add items bought
        for (int i = 0; i < buyer_num_of_bought_items; i++) {
            fscanf(buyers_fptr, "%s", item_name);

            // find if item exists
            while (bought_item != NULL) {

                // item found
                if (strcmp(bought_item->item_name, item_name) == 0) {
                    break;
                }

                // traverse
                bought_item = bought_item->nextItem;
            }

            // item was deleted

        }
    }

}
