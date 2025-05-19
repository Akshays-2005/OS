#include <stdio.h>
#include <stdlib.h>
#define MAX 100
void firstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];
    for (int i = 0; i < n; i++) allocation[i] = -1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }
    printf("\nFirst Fit Allocation:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d of size %d -> ", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("Block %d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}
void bestFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];
    for (int i = 0; i < n; i++) allocation[i] = -1;
    for (int i = 0; i < n; i++)
    {
        int bestIdx = -1;
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) bestIdx = j;
            }
        }
        if (bestIdx != -1)
        {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }
    printf("\nBest Fit Allocation:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d of size %d -> ", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("Block %d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}
void worstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];
    for (int i = 0; i < n; i++) allocation[i] = -1;
    for (int i = 0; i < n; i++)
    {
        int worstIdx = -1;
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) worstIdx = j;
            }
        }
        if (worstIdx != -1)
        {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }
    printf("\nWorst Fit Allocation:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d of size %d -> ", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("Block %d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}
void copyArray(int src[], int dest[], int size)
{
    for (int i = 0; i < size; i++) dest[i] = src[i];
}
int main()
{
    int blockSize[MAX], processSize[MAX];
    int m, n;
    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    printf("Enter size of each memory block:\n");
    for (int i = 0; i < m; i++)
    {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }
    printf("\nEnter number of processes: ");
    scanf("%d", &n);
    printf("Enter size of each process:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }
    int blockCopy[MAX];
    copyArray(blockSize, blockCopy, m);
    firstFit(blockCopy, m, processSize, n);
    copyArray(blockSize, blockCopy, m);
    bestFit(blockCopy, m, processSize, n);
    copyArray(blockSize, blockCopy, m);
    worstFit(blockCopy, m, processSize, n);
    return 0;
}
