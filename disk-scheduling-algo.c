/* Write a C program to simulate disk scheduling algorithms.
a) FCFS 
b) SCAN 
c) SSTF
d) c-LOOK */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void FCFS(int requests[], int n, int head) {
    int seek_count = 0;
    printf("\nFCFS Order: %d", head);
    for (int i = 0; i < n; i++) {
        seek_count += abs(requests[i] - head);
        head = requests[i];
        printf(" -> %d", head);
    }
    printf("\nTotal seek operations = %d\n", seek_count);
}

void SSTF(int requests[], int n, int head) {
    int seek_count = 0;
    int visited[n];
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    printf("\nSSTF Order: %d", head);

    for (int i = 0; i < n; i++) {
        int min = INT_MAX, index = -1;
        for (int j = 0; j < n; j++) {
            int diff = abs(requests[j] - head);
            if (!visited[j] && diff < min) {
                min = diff;
                index = j;
            }
        }
        seek_count += abs(requests[index] - head);
        head = requests[index];
        visited[index] = 1;
        printf(" -> %d", head);
    }
    printf("\nTotal seek operations = %d\n", seek_count);
}

void SCAN(int requests[], int n, int head, int disk_size, int direction) {
    int seek_count = 0;
    int temp[n + 1];
    for (int i = 0; i < n; i++)
        temp[i] = requests[i];
    temp[n] = head;
    n++;

  
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (temp[i] > temp[j]) {
                int t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }

    int pos;
    for (pos = 0; pos < n; pos++)
        if (temp[pos] == head)
            break;

    printf("\nSCAN Order: ");
    if (direction == 0) { 
        for (int i = pos; i >= 0; i++) {
            printf("%d ", temp[i]);
            if (i > 0)
                seek_count += abs(temp[i] - temp[i - 1]);
        }
        seek_count += temp[0]; 
        printf("0 ");
        for (int i = pos + 1; i < n; i++) {
            printf("%d ", temp[i]);
            if (i > pos + 1)
                seek_count += abs(temp[i] - temp[i - 1]);
            else
                seek_count += abs(temp[i] - 0);
        }
    } else { 
        for (int i = pos; i < n; i++) {
            printf("%d ", temp[i]);
            if (i < n - 1)
                seek_count += abs(temp[i] - temp[i + 1]);
        }
        seek_count += (disk_size - 1 - temp[n - 1]); 
        printf("%d ", disk_size - 1);
        for (int i = pos - 1; i >= 0; i--) {
            printf("%d ", temp[i]);
            if (i < pos - 1)
                seek_count += abs(temp[i] - temp[i + 1]);
            else
                seek_count += abs(temp[i] - (disk_size - 1));
        }
    }
    printf("\nTotal seek operations = %d\n", seek_count);
}

void C_LOOK(int requests[], int n, int head) {
    int seek_count = 0;
    int temp[n + 1];
    for (int i = 0; i < n; i++)
        temp[i] = requests[i];
    temp[n] = head;
    n++;

    // Sort
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (temp[i] > temp[j]) {
                int t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }

    int pos;
    for (pos = 0; pos < n; pos++)
        if (temp[pos] == head)
            break;

    printf("\nC-LOOK Order: ");
    for (int i = pos; i < n; i++) {
        printf("%d ", temp[i]);
        if (i < n - 1)
            seek_count += abs(temp[i] - temp[i + 1]);
    }
    if (pos > 0) {
        seek_count += abs(temp[n - 1] - temp[0]);
        printf("%d ", temp[0]);
        for (int i = 1; i < pos; i++) {
            printf("%d ", temp[i]);
            seek_count += abs(temp[i] - temp[i - 1]);
        }
    }
    printf("\nTotal seek operations = %d\n", seek_count);
}

int main() {
    int requests[] = {82, 170, 43, 140, 24, 16, 190};
    int n = sizeof(requests) / sizeof(requests[0]);
    int head = 50;
    int disk_size = 200;

    printf("Disk Scheduling Simulation:\n");
    printf("Request queue: ");
    for (int i = 0; i < n; i++)
        printf("%d ", requests[i]);
    printf("\nInitial Head Position: %d\n", head);

    FCFS(requests, n, head);
    SSTF(requests, n, head);
    SCAN(requests, n, head, disk_size, 1); 
    C_LOOK(requests, n, head);

    return 0;
}


/* OUTPUT
Disk Scheduling Simulation:
Request queue: 82 170 43 140 24 16 190 
Initial Head Position: 50

FCFS Order: 50 -> 82 -> 170 -> 43 -> 140 -> 24 -> 16 -> 190
Total seek operations = 642

SSTF Order: 50 -> 43 -> 24 -> 16 -> 82 -> 140 -> 170 -> 190
Total seek operations = 322

SCAN Order: 50 82 140 170 190 199 43 24 16 0 
Total seek operations = 391

C-LOOK Order: 50 82 140 170 190 16 24 43 
Total seek operations = 322
*/
