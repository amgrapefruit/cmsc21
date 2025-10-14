

// libraries
#define STRLENGTH 50

// function declarations

int main() {
    // ...
    int crush_num = 0; // for num of crushes
    char *my_name; // string for own name
    my_name = (char *) malloc(STRLENGTH * sizeof(char));
    
    start(my_name, &crush_num); // input my_name and crush_num
    
    char **names; // string array for crush names
    names = (char **) malloc(crush_num * sizeof(char *));

    inputNames(names, crush_num);

    //...
    for (int i = 0; i < crush_num; i++) {
        flames(my_name, names[i], i+1);
    }
    //...
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

        name1[i] = tolower(name1[i]);

        // find a similar char in second string
        for (int j = 0; j < strlen(name2); j++) {
            if (!isalpha(name2[j])){
                continue;
            }

            name2[j] = tolower(name2[j]);

            if (name1[i] == name2[j]) {
                // remove similar characters
                name1[i] = ' ';
                name2[j] = ' ';
                break;
            }
        }
    }

    // count all alphanetic characters
    int count = 0;

    for (int i = 0; i < strlen(name1); i++) {
        // check if alphabet
        if (isalpha(name1[i])) {
            count++;
        }
    }

    for (int i = 0; i < strlen(name2); i++) {
        // check if alphabet
        if (isalpha(name2[i])) {
            count++;
        }
    }
    printf("Remaining character count: %i\n", count);
    
    char flam[] = "flames";
    
    
    // delete char in flames until one char remains
    while (strlen(flam) > 1) {
        deleteCharByIndex(flam, (count % strlen(flam) - 1));
    }
    
    // print results
}