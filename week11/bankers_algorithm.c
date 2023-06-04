#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3

int available[NUMBER_OF_RESOURCES] = {3, 3, 2};

int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

// sequence array, which satisfies the safety criteria
int sequence[NUMBER_OF_CUSTOMERS];

int customer, i, j, order, flag;

void calc_need() {
    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        for (j = 0; j < NUMBER_OF_RESOURCES; j++)
            need[i][j] = maximum[i][j] - allocation[i][j];
    }
}

int isSafe() {
    int work[NUMBER_OF_RESOURCES], finish[NUMBER_OF_CUSTOMERS];
    memcpy(work, available, NUMBER_OF_RESOURCES * sizeof(int));
    memset(finish, 0, NUMBER_OF_CUSTOMERS * sizeof(int));

    i = 0;
    j = 0;
    order = 0;
    flag = 0;

    /* 
    TODO : Write Safety Algorithm with record sequence
    -------- Return Value --------
    1 : Following System is safe.
    0 : Following System is unsafe.
    */

    for (customer = 0; customer < NUMBER_OF_CUSTOMERS; customer++) {
        /* Write Code */
        if (finish[customer] == 0) {
            int resources_satisfied = 1;
            for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
                if (need[customer][j] > work[j]) {
                    resources_satisfied = 0;
                    break;
                }
            }
            if (resources_satisfied) {
                finish[customer] = 1;
                sequence[order] = customer;
                for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
                    work[j] += allocation[customer][j];
                }                    
                flag = 1;
                break;
            }
        }
    }

    return 1;
}

int main() {
    calc_need();

    if (isSafe()) {
        printf("< ");
        for (i = 0; i < NUMBER_OF_CUSTOMERS; i++){
            printf("P%d ",sequence[i]);
        }
        printf(">\n");
    } else {
        printf("The following system is not safe.");
    }

    return 0;
}