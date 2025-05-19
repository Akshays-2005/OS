#include <stdio.h>
int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int bt[n], wt[n], tat[n];
    float total_wt = 0, total_tat = 0;
    printf("Enter burst times:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d: ", i + 1);
        scanf("%d", &bt[i]);
    }
    wt[0] = 0;
    for (int i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1];
    }
    for (int i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("Process\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }
    printf("\nAvg WT: %.2f", total_wt / n);
    printf("\nAvg TAT: %.2f\n", total_tat / n);
    return 0;
}
