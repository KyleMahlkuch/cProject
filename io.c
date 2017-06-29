/*
 * This is a project meant to help you become more proficient at the C language
 */

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.c"


linkedList *master_list;

void main(int argc, char **argv) {
    int i;    
    node* a;
    char buff[100];
    char *err;

    master_list = list_create();

    while (1) {
        printf("Please enter an integer or hit enter to end.\n");
        fgets(buff,100,stdin);
        if (buff[0] != '\n') {
            i = strtol(buff, &err, 10);
            insert(i, master_list);
        } else {
            break;
        }
    }

    printf("done inserting into list.\n");
    printf("the list:\n");

    printList(master_list);

}
