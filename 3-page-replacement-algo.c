/* Write a C program to simulate page replacement algorithms. 
a) FIFO
b) LRU
c) Optimal */

#include <stdio.h>
#include <stdlib.h>

int search(int key, int frame[], int n) {
    for (int i = 0; i < n; i++) {
        if (frame[i] == key)
            return 1;
    }
    return 0;
}

int findLRU(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int predict(int pages[], int n, int frame[], int fr, int index) {
    int res = -1, farthest = index;
    for (int i = 0; i < fr; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }
    return (res == -1) ? 0 : res;
}

void fifo(int pages[], int n, int fr) {
    int frame[10], front = 0, count = 0;
    printf("\nFIFO Page Replacement\n");

    for (int i = 0; i < fr; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++) {
        if (!search(pages[i], frame, fr)) {
            frame[front] = pages[i];
            front = (front + 1) % fr;
            count++;
            printf("Page %d => ", pages[i]);
            for (int j = 0; j < fr; j++)
                if (frame[j] != -1) printf("%d ", frame[j]);
            printf("\n");
        } else {
            printf("Page %d => Hit\n", pages[i]);
        }
    }
    printf("Total Page Faults (FIFO): %d\n", count);
}

void lru(int pages[], int n, int fr) {
    int frame[10], time[10], count = 0, counter = 0;
    printf("\nLRU Page Replacement\n");

    for (int i = 0; i < fr; i++) {
        frame[i] = -1;
        time[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        if (search(pages[i], frame, fr)) {
            for (int j = 0; j < fr; j++)
                if (frame[j] == pages[i])
                    time[j] = ++counter;
            printf("Page %d => Hit\n", pages[i]);
        } else {
            int pos = -1;
            for (int j = 0; j < fr; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }
            if (pos == -1)
                pos = findLRU(time, fr);

            frame[pos] = pages[i];
            time[pos] = ++counter;
            count++;

            printf("Page %d => ", pages[i]);
            for (int j = 0; j < fr; j++)
                if (frame[j] != -1) printf("%d ", frame[j]);
            printf("\n");
        }
    }
    printf("Total Page Faults (LRU): %d\n", count);
}

void optimal(int pages[], int n, int fr) {
    int frame[10], count = 0;
    printf("\nOptimal Page Replacement\n");

    for (int i = 0; i < fr; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++) {
        if (!search(pages[i], frame, fr)) {
            int pos = -1;
            for (int j = 0; j < fr; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }
            if (pos == -1)
                pos = predict(pages, n, frame, fr, i + 1);

            frame[pos] = pages[i];
            count++;

            printf("Page %d => ", pages[i]);
            for (int j = 0; j < fr; j++)
                if (frame[j] != -1) printf("%d ", frame[j]);
            printf("\n");
        } else {
            printf("Page %d => Hit\n", pages[i]);
        }
    }
    printf("Total Page Faults (Optimal): %d\n", count);
}

int main() {
    int n, fr;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &fr);

    fifo(pages, n, fr);
    lru(pages, n, fr);
    optimal(pages, n, fr);

    return 0;
}

/* OUTPUT
Enter number of pages: 12
Enter page reference string:
7 0 1 2 0 3 0 4 2 3 0 3
Enter number of frames: 3

FIFO Page Replacement
Page 7 => 7
Page 0 => 7 0
Page 1 => 7 0 1
Page 2 => 0 1 2
Page 0 => Hit
Page 3 => 1 2 3
Page 0 => 2 3 0
Page 4 => 3 0 4
Page 2 => 0 4 2
Page 3 => 4 2 3
Page 0 => 2 3 0
Page 3 => Hit
Total Page Faults (FIFO): 9

LRU Page Replacement
Page 7 => 7
Page 0 => 7 0
Page 1 => 7 0 1
Page 2 => 0 1 2
Page 0 => Hit
Page 3 => 1 2 3
Page 0 => 2 3 0
Page 4 => 3 0 4
Page 2 => 0 4 2
Page 3 => 4 2 3
Page 0 => 2 3 0
Page 3 => Hit
Total Page Faults (LRU): 9

Optimal Page Replacement
Page 7 => 7
Page 0 => 7 0
Page 1 => 7 0 1
Page 2 => 0 1 2
Page 0 => Hit
Page 3 => 1 2 3
Page 0 => 2 3 0
Page 4 => 3 0 4
Page 2 => 0 4 2
Page 3 => 4 2 3
Page 0 => 2 3 0
Page 3 => Hit
Total Page Faults (Optimal): 8
*/
