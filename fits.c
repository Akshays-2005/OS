#include <stdio.h>

#define MAX_BLOCKS 100
#define MAX_PROCESSES 100

void firstFit(int blockSize[], int blocks, int processSize[], int processes);
void bestFit(int blockSize[], int blocks, int processSize[], int processes);
void worstFit(int blockSize[], int blocks, int processSize[], int processes);

int main() {
    int blockSize[MAX_BLOCKS], processSize[MAX_PROCESSES];
    int blocks, processes, choice;

    printf("Enter number of memory blocks: ");
    scanf("%d", &blocks);
    printf("Enter size of each block:\n");
    for (int i = 0; i < blocks; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    printf("Enter number of processes: ");
    scanf("%d", &processes);
    printf("Enter size of each process:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }
    printf("\nChoose Allocation Strategy:\n");
    printf("1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Exit\n");
    while (1) {
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        int tempBlockSize[MAX_BLOCKS];
        for (int i = 0; i < blocks; i++) {
            tempBlockSize[i] = blockSize[i];
        }

        switch (choice) {
            case 1:
                firstFit(tempBlockSize, blocks, processSize, processes);
                break;
            case 2:
                bestFit(tempBlockSize, blocks, processSize, processes);
                break;
            case 3:
                worstFit(tempBlockSize, blocks, processSize, processes);
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Please select 1-4.\n");
        }
    }
    return 0;
}

void firstFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX_PROCESSES];
    for (int i = 0; i < processes; i++) allocation[i] = -1;
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }
    printf("\nFirst Fit Allocation:\n");
    printf("Process\t\t Block\n");
    for (int i = 0; i < processes; i++) {
        if (allocation[i] != -1)
            printf("%d\t\t%d\n", i + 1, allocation[i] + 1);
        else
            printf("%d\t\tNot Allocated\n", i + 1);
    }
    printf("\nBlock Status:\n");
    printf("Block Number\tRemaining Size\n");
    for (int i = 0; i < blocks; i++){
            printf("\n%d\t\t%d", i+1, blockSize[i]);
    }
}

void bestFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX_PROCESSES];
    for (int i = 0; i < processes; i++) allocation[i] = -1;
    for (int i = 0; i < processes; i++) {
        int bestIdx = -1;
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }
    printf("\nBest Fit Allocation:\n");
    printf("Process\t\t Block\n");
    for (int i = 0; i < processes; i++) {
        if (allocation[i] != -1)
            printf("%d\t\t%d\n", i + 1, allocation[i] + 1);
        else
            printf("%d\t\tNot Allocated\n", i + 1);
    }
    printf("\nBlock Status:\n");
    printf("Block Number\tRemaining Size\n");
    for (int i = 0; i < blocks; i++){
            printf("\n%d\t\t%d", i+1, blockSize[i]);
    }
}

void worstFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX_PROCESSES];
    for (int i = 0; i < processes; i++) allocation[i] = -1;
    for (int i = 0; i < processes; i++) {
        int worstIdx = -1;
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }
    printf("\nWorst Fit Allocation:\n");
    printf("Process\t\t Block\n");
    for (int i = 0; i < processes; i++) {
        if (allocation[i] != -1)
            printf("%d\t\t%d\n", i + 1, allocation[i] + 1);
        else
            printf("%d\t\tNot Allocated\n", i + 1);
    }
    printf("\nBlock Status:\n");
    printf("Block Number\tRemaining Size\n");
    for (int i = 0; i < blocks; i++){
            printf("\n%d\t\t%d", i+1, blockSize[i]);
    }
}

/*Output:
Enter number of memory blocks: 5
Enter size of each block:
Block 1: 100
Block 2: 500
Block 3: 200
Block 4: 300
Block 5: 600
Enter number of processes: 4
Enter size of each process:
Process 1: 212
Process 2: 417
Process 3: 112
Process 4: 426

Choose Allocation Strategy:
1. First Fit
2. Best Fit
3. Worst Fit
4. Exit

Enter choice: 1

First Fit Allocation:
Process          Block
1               2
2               5
3               2
4               Not Allocated

Block Status:
Block Number    Remaining Size

1               100
2               176
3               200
4               300
5               183
Enter choice: 2

Best Fit Allocation:
Process          Block
1               4
2               2
3               3
4               5

Block Status:
Block Number    Remaining Size

1               100
2               83
3               88
4               88
5               174
Enter choice: 3

Worst Fit Allocation:
Process          Block
1               5
2               2
3               5
4               Not Allocated

Block Status:
Block Number    Remaining Size

1               100
2               83
3               200
4               300
5               276
Enter choice: 4
Exiting...
*/
