/*
 * This is a project meant to help you become more proficient at the C language
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <sched.h>

#include "linked_list.c"


linkedList *master_list;

void main(int argc, char **argv) {
    int32_t i;    
    node* a;
    char buff[100];
    char *err;
    struct utsname sys_info;
    struct sysinfo info;

    master_list = list_create();

    sysinfo(&info);
    uname(&sys_info);

    printf("Begin program... Welcome!\n");
    printf("Your process ID is: %d\n", getpid());
    printf("Your kernel version is: %s\n", sys_info.version); //issues here .version
    printf("Total RAM of system: %ld\n", info.totalram);
    printf("Number of NUMA nodes founds: %d\n",sched_getcpu());

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
