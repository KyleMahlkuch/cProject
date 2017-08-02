/*
 * This is a project meant to help you become more proficient at the C language
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <sys/time.h>
#include <sched.h>
#include <math.h>
#include <time.h>

#include "linked_list.c"


#define SHIFT_LEFT(x) x << 16
#define SHIFT_RIGHT(x) x >> 16
#define VAL(x) x & 0xFF
#define REP(x) x >> 16


linkedList *master_list;
int32_t list_length;

int32_t my_bin_search (int32_t value, int64_t* data, int type) {
    int length;
    int32_t i;
    int32_t search_val;
    int32_t max, min;
    int32_t middle;
    node* a;

    if (type == 0) {
        //then list
        length = master_list->size;
    }
    if (type == 1) {
        //then array
        length = list_length;
    }

    search_val = length/2;
    max = length;
    min = -1;

    a = master_list->head;

    while (1) {
        if (search_val == max) {
            if (value == middle) {
                return search_val;
            } else {
                return -1;
            }

        } else if (search_val == min) {
            if (value == middle) {
                return search_val;
            } else {
                return -1;
            }
        }


        //update middle
        if (type == 0) {
            //then list
/*            while (a->data != search_val) {
                if (a->data < search_val) {
                    a = a->next;
                } else {
                    a = a->prev;
                }

            }

*/
            a = master_list->head;
             for (i=0; i<search_val; i++){
                 a = a->next;
             }
             middle = a->data;
 
        }
        if (type == 1) {
            //then array
            middle = VAL(data[search_val]);
        }



        if (value == middle) {
            return search_val;
        }
        if (value < middle) {
            max = search_val;
            search_val = (min + max) /2;
        } else {
            min = search_val;
            search_val = (min + max) / 2;
        }
    }

}

void main(int argc, char **argv) {
    int32_t i;    
    node* a;
    char buff[100];
    char *err;
    struct utsname sys_info;
    struct sysinfo info;
    int64_t *list_array;
    int64_t dummy;
    struct timespec start={0,0}, end={0,0};
    long secondsL, secondsA;

    master_list = list_create();

    sysinfo(&info);
    uname(&sys_info);

    printf("Begin program... Welcome!\n");
    printf("Your process ID is: %d\n", getpid());
    printf("Your kernel version is: %s\n", sys_info.version); //issues here .version
    printf("Total RAM of system: %ld\n", info.totalram);
    printf("Number of NUMA nodes founds: %d\n",sched_getcpu());

    while (1) {
        printf("Please enter an integer or hit return to end.\n> ");
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

    list_array = (int64_t*)malloc(sizeof(int64_t)*master_list->size);
    list_length = 0;

    a = master_list->head;
    for ( i = 0; i < master_list->size; i++ ) {        
        dummy = SHIFT_LEFT(a->repetitions) | a->data;
        list_array[i] = dummy;
        list_length++;
        a = a->next;
    }   

    printf("\nEntering search mode...");

    int32_t list_out;
    int32_t array_out;


    while (1) {
        printf("\nPlease enter an integer you want to search for or hit return to end.\nType 'l' to view the list again.\n> ");
        fgets(buff,100,stdin);

        if (buff[0] == 'l') {

            printf("the list:\n");
            printList(master_list);

        } else if (buff[0] != '\n') {
            i = strtol(buff, &err, 10);

            printf("searching for: %d\n", i);

            clock_gettime(CLOCK_MONOTONIC, &start);
            list_out = my_bin_search (i, list_array, 0);
            clock_gettime(CLOCK_MONOTONIC, &end);
            secondsL = ((double)end.tv_nsec - start.tv_nsec);

            clock_gettime(CLOCK_MONOTONIC, &start);
            array_out = my_bin_search (i, list_array, 1);
            clock_gettime(CLOCK_MONOTONIC, &end);
            printf("%d\n", end.tv_nsec);
            secondsA = ((double)end.tv_nsec - start.tv_nsec);
            
            printf("list pos: %d\narray pos: %d\n", list_out, array_out);
            printf("list usec: %.3f\narray usec: %.3f\n", secondsL/1000.0, secondsA/1000.0);

        } else {
            printf("Size of List: %.3fKB\n", master_list->size * sizeof(struct node)/1000.0);
            printf("Size of Array: %.3fKB\n\n", list_length * sizeof(int64_t)/1000.0);
            break;
        }
    }

}













