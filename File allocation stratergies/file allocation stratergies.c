#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BLOCKS 100
#define MAX_FILES 10
#define MAX_BLOCKS_PER_FILE 10
int memory[MAX_BLOCKS];
typedef struct {
    char filename[20];
    int startBlock;
    int length;
} SequentialFile;
typedef struct {
    char filename[20];
    int indexBlock;
    int blocks[MAX_BLOCKS_PER_FILE];
    int count;
} IndexedFile;
typedef struct {
    char filename[20];
    int blocks[MAX_BLOCKS_PER_FILE];
    int count;
} LinkedFile;
SequentialFile seqFiles[MAX_FILES];
int seqFileCount = 0;
IndexedFile indexedFiles[MAX_FILES];
int indexedFileCount = 0;
LinkedFile linkedFiles[MAX_FILES];
int linkedFileCount = 0;
void allocateSequentialFile() {
    char filename[20];
    int length, startBlock;
    printf("\nEnter file name: ");
    scanf("%s", filename);
    printf("Enter number of blocks required (max %d): ", MAX_BLOCKS_PER_FILE);
    scanf("%d", &length);
    if (length > MAX_BLOCKS_PER_FILE || length <= 0) {
        printf("Invalid length. Max %d blocks allowed.\n", MAX_BLOCKS_PER_FILE);
        return;
    }
    int found = 0;
    for (startBlock = 0; startBlock <= MAX_BLOCKS - length; startBlock++) {
        int j;
        for (j = 0; j < length; j++) {
            if (memory[startBlock + j] == 1) break;
        }
        if (j == length) {
            found = 1;
            break;
        }
    }
    if (found) {
        for (int i = startBlock; i < startBlock + length; i++) {
            memory[i] = 1;
        }
        strcpy(seqFiles[seqFileCount].filename, filename);
        seqFiles[seqFileCount].startBlock = startBlock;
        seqFiles[seqFileCount].length = length;
        seqFileCount++;
        printf("File allocated successfully from block %d to %d.\n", startBlock, startBlock + length - 1);
    } else {
        printf("No sufficient contiguous blocks available. Allocation failed.\n");
    }
}
void allocateIndexedFile() {
    char filename[20];
    int indexBlock, count, block;
    printf("\nEnter file name: ");
    scanf("%s", filename);
    printf("Enter index block: ");
    scanf("%d", &indexBlock);
    if (indexBlock < 0 || indexBlock >= MAX_BLOCKS || memory[indexBlock] == 1) {
        printf("Invalid or already allocated index block. Allocation failed.\n");
        return;
    }
    printf("Enter number of blocks required (max %d): ", MAX_BLOCKS_PER_FILE);
    scanf("%d", &count);
    if (count > MAX_BLOCKS_PER_FILE || count <= 0) {
        printf("Invalid block count. Allocation failed.\n");
        return;
    }
    int blocks[MAX_BLOCKS_PER_FILE];
    printf("Enter %d block numbers: ", count);
    for (int i = 0; i < count; i++) {
        scanf("%d", &block);
        if (block < 0 || block >= MAX_BLOCKS || memory[block] == 1 || block == indexBlock) {
            printf("Invalid or already allocated block %d. Allocation failed.\n", block);
            return;
        }
        blocks[i] = block;
    }
    memory[indexBlock] = 1;
    for (int i = 0; i < count; i++) {
        memory[blocks[i]] = 1;
    }
    strcpy(indexedFiles[indexedFileCount].filename, filename);
    indexedFiles[indexedFileCount].indexBlock = indexBlock;
    indexedFiles[indexedFileCount].count = count;
    for (int i = 0; i < count; i++) {
        indexedFiles[indexedFileCount].blocks[i] = blocks[i];
    }
    indexedFileCount++;
    printf("File allocated using Indexed Allocation.\n");
}
void allocateLinkedFile() {
    char filename[20];
    int count, block;
    printf("\nEnter file name: ");
    scanf("%s", filename);
    printf("Enter number of blocks required (max %d): ", MAX_BLOCKS_PER_FILE);
    scanf("%d", &count);
    if (count > MAX_BLOCKS_PER_FILE || count <= 0) {
        printf("Invalid block count. Allocation failed.\n");
        return;
    }
    int blocks[MAX_BLOCKS_PER_FILE];
    printf("Enter %d block numbers: ", count);
    for (int i = 0; i < count; i++) {
        scanf("%d", &block);
        if (block < 0 || block >= MAX_BLOCKS || memory[block] == 1) {
            printf("Invalid or already allocated block %d. Allocation failed.\n", block);
            return;
        }
        blocks[i] = block;
    }
    for (int i = 0; i < count; i++) {
        memory[blocks[i]] = 1;
    }
    strcpy(linkedFiles[linkedFileCount].filename, filename);
    linkedFiles[linkedFileCount].count = count;
    for (int i = 0; i < count; i++) {
        linkedFiles[linkedFileCount].blocks[i] = blocks[i];
    }
    linkedFileCount++;
    printf("File allocated using Linked Allocation.\n");
}
void displayAllocatedFiles() {
    printf("\n=== Sequential Allocation ===\n");
    printf("Filename\tStart\tLength\tBlocks\n");
    for (int i = 0; i < seqFileCount; i++) {
        printf("%s\t\t%d\t%d\t", seqFiles[i].filename, seqFiles[i].startBlock, seqFiles[i].length);
        for (int j = 0; j < seqFiles[i].length; j++) {
            printf("%d ", seqFiles[i].startBlock + j);
        }
        printf("\n");
    }
    printf("\n=== Indexed Allocation ===\n");
    printf("Filename\tIndexBlock\tBlocks\n");
    for (int i = 0; i < indexedFileCount; i++) {
        printf("%s\t\t%d\t\t", indexedFiles[i].filename, indexedFiles[i].indexBlock);
        for (int j = 0; j < indexedFiles[i].count; j++) {
            printf("%d ", indexedFiles[i].blocks[j]);
        }
        printf("\n");
    }
    printf("\n=== Linked Allocation ===\n");
    printf("Filename\tBlocks\n");
    for (int i = 0; i < linkedFileCount; i++) {
        printf("%s\t\t", linkedFiles[i].filename);
        for (int j = 0; j < linkedFiles[i].count; j++) {
            printf("%d -> ", linkedFiles[i].blocks[j]);
        }
        printf("NULL\n");
    }
}
void displayFreeBlocks() {
    printf("\nFree Memory Blocks:\n");
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (memory[i] == 0) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int choice;
    while (1) {
        printf("\nFile Allocation Menu:\n");
        printf("1. Allocate Sequential File\n");
        printf("2. Allocate Indexed File\n");
        printf("3. Allocate Linked File\n");
        printf("4. Display Allocated Files\n");
        printf("5. Display Free Memory Blocks\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                allocateSequentialFile();
                break;
            case 2:
                allocateIndexedFile();
                break;
            case 3:
                allocateLinkedFile();
                break;
            case 4:
                displayAllocatedFiles();
                break;
            case 5:
                displayFreeBlocks();
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
