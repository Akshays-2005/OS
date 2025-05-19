#include <stdio.h>
#include <stdlib.h>
int mutex = 1;
int full = 0;
int empty = 3;
int x = 0;
void wait()
{
    --mutex;
}
void signal()
{
    ++mutex;
}
void producer()
{
    if (empty != 0)
    {
        wait();
        ++full;
        --empty;
        x++;
        printf("Producer has produced: Item %d\n", x);
        signal();
    }
    else
    {
        printf("Buffer is full!\n");
    }
}
void consumer()
{
    if (full != 0)
    {
        wait();
        --full;
        ++empty;
        printf("Consumer has consumed: Item %d\n", x);
        x--;
        signal();
    }
    else
    {
        printf("Buffer is empty!\n");
    }
}
int main()
{
    int choice;
    while (1)
    {
        printf("Enter 1.Producer 2.Consumer 3.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            producer();
            break;
        case 2:
            consumer();
            break;
        case 3:
            exit(0);
        default:
            printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
