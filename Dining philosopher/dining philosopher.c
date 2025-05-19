#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX 5
int hungry[MAX] = {0};
void displayStatus(int n)
{
    for (int i = 0; i < MAX; i++)
    {
        if (hungry[i])
            printf("P %d is waiting\n", i + 1);
    }
}
void simulateEating(int id)
{
    printf("P %d is granted to eat\n", id + 1);
    sleep(1); // Simulate eating time
    printf("P %d has finished eating\n", id + 1);
}
int main()
{
    int total, hcount;
    int hungry_ids[3];
    int choice;
    printf("Enter the total number of philosophers: ");
    scanf("%d", &total);
    if (total != 5)
    {
        printf("This simulation only supports 5 philosophers.\n");
        return 1;
    }
    printf("How many are hungry: ");
    scanf("%d", &hcount);
    if (hcount > 3)
    {
        printf("Only up to 3 hungry philosophers supported in this simulation.\n");
        return 1;
    }
    for (int i = 0; i < hcount; i++)
    {
        printf("Enter philosopher %d position (1 to 5): ", i + 1);
        scanf("%d", &hungry_ids[i]);
        if (hungry_ids[i] < 1 || hungry_ids[i] > 5)
        {
            printf("Invalid position. Please enter between 1 and 5.\n");
            return 1;
        }
        hungry[hungry_ids[i] - 1] = 1;
    }
    do
    {
        printf("\n1. One can eat at a time\n2. Two can eat at a time\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Allow one philosopher to eat at any time\n");
            for (int i = 0; i < hcount; i++)
            {
                displayStatus(hcount);
                simulateEating(hungry_ids[i] - 1);
                hungry[hungry_ids[i] - 1] = 0;
            }
            break;
        case 2:
            printf("Allow two philosophers to eat at any time\n");
            for (int i = 0; i < hcount; i += 2)
            {
                displayStatus(hcount);
                simulateEating(hungry_ids[i] - 1);
                hungry[hungry_ids[i] - 1] = 0;
                if (i + 1 < hcount)
                {
                    simulateEating(hungry_ids[i + 1] - 1);

                    hungry[hungry_ids[i + 1] - 1] = 0;
                }
            }
            break;
        case 3:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice.\n");
        }
    }
    while (choice != 3);
    return 0;
}
