#include <stdio.h>
#include <stdbool.h>
#define MAX 100
bool isHit(int frame[], int page, int f)
{
    for (int i = 0; i < f; i++)
    {
        if (frame[i] == page) return true;
    }
    return false;
}
int findLRU(int time[], int f)
{
    int min = time[0], pos = 0;
    for (int i = 1; i < f; i++)
    {
        if (time[i] < min)
        {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}
int findOptimal(int pages[], int frame[], int index, int n, int f)
{
    int farthest = index, pos = -1, i, j;
    for (i = 0; i < f; i++)
    {
        for (j = index; j < n; j++)
        {
            if (frame[i] == pages[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == n) return i;
    }
    return (pos == -1) ? 0 : pos;
}
void printFrames(int frame[], int f)
{
    for (int i = 0; i < f; i++)
    {
        if (frame[i] == -1)

            printf(" ");
        else
            printf("%d ", frame[i]);
    }
    printf("\n");
}
int main()
{
    int f, n, pages[MAX];
    printf("Enter the number of Frames: ");
    scanf("%d", &f);
    printf("Enter the length of reference string: ");
    scanf("%d", &n);
    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    int frame1[MAX], front = 0, faults1 = 0;
    for (int i = 0; i < f; i++) frame1[i] = -1;
    printf("\nFIFO Page Replacement Process:\n");
    for (int i = 0; i < n; i++)
    {
        if (!isHit(frame1, pages[i], f))
        {
            frame1[front] = pages[i];
            front = (front + 1) % f;
            faults1++;
            printf("PF No. %d: ", faults1);
            printFrames(frame1, f);
        }
    }
    printf("FIFO Page Faults: %d\n", faults1);
    int frame2[MAX], time[MAX], faults2 = 0, counter = 0;
    for (int i = 0; i < f; i++) frame2[i] = -1;
    printf("\nLRU Page Replacement Process:\n");
    for (int i = 0; i < n; i++)
    {
        if (!isHit(frame2, pages[i], f))
        {
            int pos = -1;
            for (int j = 0; j < f; j++)
            {
                if (frame2[j] == -1)
                {
                    pos = j;
                    break;
                }
            }
            if (pos == -1)
                pos = findLRU(time, f);
            frame2[pos] = pages[i];
            faults2++;
            printf("PF No. %d: ", faults2);
            printFrames(frame2, f);
        }
        for (int j = 0; j < f; j++)
        {
            if (frame2[j] == pages[i]) time[j] = ++counter;
        }
    }
    printf("LRU Page Faults: %d\n", faults2);
    int frame3[MAX], faults3 = 0;
    for (int i = 0; i < f; i++) frame3[i] = -1;
    printf("\nOptimal Page Replacement Process:\n");
    for (int i = 0; i < n; i++)
    {
        if (!isHit(frame3, pages[i], f))
        {
            int pos = -1;
            for (int j = 0; j < f; j++)
            {
                if (frame3[j] == -1)
                {
                    pos = j;
                    break;
                }
            }
            if (pos == -1)
                pos = findOptimal(pages, frame3, i + 1, n, f);
            frame3[pos] = pages[i];
            faults3++;
            printf("PF No. %d: ", faults3);
            printFrames(frame3, f);
        }
    }
    printf("Optimal Page Faults: %d\n", faults3);
    return 0;
}
