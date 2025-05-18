/* Write a C program to simulate: (Any one)
a) Bankers’ algorithm for the purpose of deadlock 
avoidance */

#include <stdio.h>
#include <stdbool.h>

#define P 5  
#define R 3  
int main() {
    int i, j, k;

   
    int alloc[P][R] = { {0, 1, 0},   
                        {2, 0, 0}, 
                        {3, 0, 2},   
                        {2, 1, 1},  
                        {0, 0, 2} };

    int max[P][R] =   { {7, 5, 3},  
                        {3, 2, 2}, 
                        {9, 0, 2},   
                        {2, 2, 2},  
                        {4, 3, 3} }; 

    int avail[R] = {3, 3, 2}; 

    int need[P][R]; 
    for (i = 0; i < P; i++) {
        for (j = 0; j < R; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    bool finish[P] = {0};
    int safeSeq[P];
    int work[R];
    for (i = 0; i < R; i++)
        work[i] = avail[i];

    int count = 0;
    while (count < P) {
        bool found = false;
        for (i = 0; i < P; i++) {
            if (!finish[i]) {
                bool canProceed = true;
                for (j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        canProceed = false;
                        break;
                    }
                }

                if (canProceed) {
                    for (k = 0; k < R; k++)
                        work[k] += alloc[i][k];

                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("System is not in a safe state.\n");
            return 1;
        }
    }

 
    printf("System is in a safe state.\nSafe sequence is: ");
    for (i = 0; i < P; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");

    return 0;
}

/* OUTPUT
System is in a safe state.
Safe sequence is: P1 P3 P4 P0 P2 
*/
