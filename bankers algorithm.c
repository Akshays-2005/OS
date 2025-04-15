#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int main() {
    int n, m;
    int alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
    int avail[MAX];
    int i, j, k;

    printf("Enter number of processes -- ");
    scanf("%d", &n);
    printf("Enter number of resources -- ");
    scanf("%d", &m);

    // Input Allocation and Max matrix
    for (i = 0; i < n; i++) {
        printf("Enter details for P%d\n", i);
        printf("Enter allocation -- ");
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
        printf("Enter Max -- ");
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input Available resources
    printf("Enter Available Resources -- ");
    for (i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // Calculate Need matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Handle Request
    int pid, req[MAX];
    printf("Enter New Request Details -- \n");
    printf("Enter pid -- ");
    scanf("%d", &pid);
    printf("Enter Request for Resources -- ");
    for (i = 0; i < m; i++) {
        scanf("%d", &req[i]);
        if (req[i] > need[pid][i]) {
            printf("Request exceeds maximum claim.\n");
            return 0;
        }
        if (req[i] > avail[i]) {
            printf("Resources not available.\n");
            return 0;
        }
    }

    // Temporarily allocate requested resources
    for (i = 0; i < m; i++) {
        avail[i] -= req[i];
        alloc[pid][i] += req[i];
        need[pid][i] -= req[i];
    }

    // Safety algorithm
    bool finish[MAX] = {false};
    int work[MAX];
    for (i = 0; i < m; i++) work[i] = avail[i];
    int count = 0, safeSeq[MAX];

    while (count < n) {
        bool found = false;
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                for (j = 0; j < m; j++)
                    if (need[i][j] > work[j])
                        break;
                if (j == m) {
                    for (k = 0; k < m; k++)
                        work[k] += alloc[i][k];
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;

                    printf("P%d is visited( ", i);
                    for (k = 0; k < m; k++) printf("%d ", work[k]);
                    printf(")\n");
                }
            }
        }
        if (!found) break;
    }

    if (count < n) {
        printf("SYSTEM IS NOT IN SAFE STATE\n");
    } else {
        printf("SYSTEM IS IN SAFE STATE\n");
        printf("The Safe Sequence is -- ( ");
        for (i = 0; i < n; i++) {
            printf("P%d ", safeSeq[i]);
        }
        printf(")\n");
    }

    // Print summary table
    printf("\n%-10s %-15s %-10s %-10s\n", "Process", "Allocation", "Max", "Need");
    for (i = 0; i < n; i++) {
        printf("P%-9d ", i);
        for (j = 0; j < m; j++) printf("%d ", alloc[i][j]);
        printf("      ");
        for (j = 0; j < m; j++) printf("%d ", max[i][j]);
        printf("      ");
        for (j = 0; j < m; j++) printf("%d ", need[i][j]);
        printf("\n");
    }

    return 0;
}


/* Output:
Enter number of processes -- 5
Enter number of resources -- 3
Enter details for P0
Enter allocation -- 0 1 0
Enter Max -- 7 5 3
Enter details for P1
Enter allocation -- 2 0 0
Enter Max -- 3 2 2
Enter details for P2
Enter allocation -- 3 0 2
Enter Max -- 9 0 2
Enter details for P3
Enter allocation -- 2 1 1
Enter Max -- 2 2 2
Enter details for P4
Enter allocation -- 0 0 2
Enter Max -- 4 3 3
Enter Available Resources -- 3 3 2
Enter New Request Details --
Enter pid -- 1
Enter Request for Resources -- 1 0 2
P1 is visited( 5 3 2 )
P3 is visited( 7 4 3 )
P4 is visited( 7 4 5 )
P0 is visited( 7 5 5 )
P2 is visited( 10 5 7 )
SYSTEM IS IN SAFE STATE
The Safe Sequence is -- ( P1 P3 P4 P0 P2 )

Process    Allocation      Max        Need
P0         0 1 0       7 5 3       7 4 3
P1         3 0 2       3 2 2       0 2 0
P2         3 0 2       9 0 2       6 0 0
P3         2 1 1       2 2 2       0 1 1
P4         0 0 2       4 3 3       4 3 1
*/
