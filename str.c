#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    
    char name[20]="hi";
    char *prompt;

    prompt = (char *) malloc(sizeof(char) * 5);

    //name = "hiu";
    prompt = "hello";

    //scanf("%s", prompt);
    //prompt = "name"; //will this work?
    //strcpy(name, prompt);

    printf("n: %s, p: %s\n", name, prompt);
    /*
    char name[20], *name2 = "(char *) malloc(sizeof(char) * 8)";
    char *prompt = "What is your name?";

    printf("%s",prompt);
    scanf("%s",name);
    scanf("%s",name2); //will this work?

    printf("Your name is %s;    %s.\n",name, name2);*/

    return 0;
}