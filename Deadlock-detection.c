/* Write a C program to simulate: 
Deadlock Detection */

#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int main() {
    int n, m; 
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int request[MAX_PROCESSES][MAX_RESOURCES];
    int available[MAX_RESOURCES];
    bool finish[MAX_PROCESSES];

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter Request Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &request[i][j]);

    printf("Enter Available Resources (length %d):\n", m);
    for (int j = 0; j < m; j++)
        scanf("%d", &available[j]);

    for (int i = 0; i < n; i++)
        finish[i] = false;

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (request[i][j] > available[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < m; j++)
                        available[j] += allocation[i][j];
                    finish[i] = true;
                    found = true;
                    count++;
                    printf("Process P%d has completed.\n", i);
                }
            }
        }
        if (!found) {
            break;
        }
    }

    bool deadlock = false;
    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            deadlock = true;
            printf("Process P%d is in deadlock.\n", i);
        }
    }

    if (!deadlock)
        printf("No deadlock detected in the system.\n");
    else
        printf("Deadlock detected in the system.\n");

    return 0;
}

/* OUTPUT 
Enter number of processes: 5
Enter number of resources: 3
Enter Allocation Matrix (5 x 3):
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
Enter Request Matrix (5 x 3):
0 0 0
2 0 2
0 0 0
1 0 0
0 0 2
Enter Available Resources (length 3):
0 0 0

Process P0 has completed.
Process P2 has completed.
Process P3 has completed.
Process P1 has completed.
Process P4 has completed.
No deadlock detected in the system.
*/


