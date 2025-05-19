#include <stdio.h>
int main() {
    int n, i, j, pos;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int at[n], bt[n], wt[n], tat[n], p[n];
    float total_wt = 0, total_tat = 0;
    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (i = 0; i < n; i++) {
        p[i] = i + 1;
        printf("Process %d (AT BT): ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
    }
    for (i = 0; i < n - 1; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (bt[j] < bt[pos])
            pos = j;
        }
        int temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;
        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }
    wt[0] = 0;
    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
    }
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("Process\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\n", p[i], bt[i], wt[i], tat[i]);
    }
    printf("\nAvg WT: %.2f", total_wt / n);
    printf("\nAvg TAT: %.2f\n", total_tat / n);
    return 0;
}
