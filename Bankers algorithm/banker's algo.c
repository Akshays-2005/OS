#include <stdio.h>
#include <stdbool.h>
#define MAX_P 10
#define MAX_R 10
int main()
{
    int n, m;
    int	alloc[MAX_P][MAX_R],max[MAX_P][MAX_R],need[MAX_P][MAX_R], avail[MAX_R];
    int i, j, k;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);
    for (i = 0; i < n; i++)
    {
        printf("Enter allocation for P%d: ", i);
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);
        printf("Enter max for P%d: ", i);
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);
    }
    printf("Enter available resources: ");
    for (i = 0; i < m; i++)
        scanf("%d", &avail[i]);
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    bool finish[MAX_P] = {0};
    int safeSeq[MAX_P];
    int work[MAX_R];
    for (i = 0; i < m; i++)
        work[i] = avail[i];
    int count = 0;
    while (count < n)
    {
        bool found = false;
        for (i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                bool can_allocate = true;
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate)
                {
                    for (k = 0; k < m; k++) work[k] += alloc[i][k];
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found)
        {
            printf("System is not in a safe state.\n");
            return 1;
        }
    }
    printf("System is in a safe state.\nSafe sequence is: ");
    for (i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");
    printf("\nProcess\tAllocation\tMax\t\tNeed\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d\t", i);
        for (j = 0; j < m; j++)
            printf("%d ", alloc[i][j]);
        printf("\t\t");
        for (j = 0; j < m; j++) printf("%d ", max[i][j]);
        printf("\t\t");
        for (j = 0; j < m; j++) printf("%d ", need[i][j]);
        printf("\n");
    }
    return 0;
}
