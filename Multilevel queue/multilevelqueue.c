#include <stdio.h>
int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int bt1[n], tat1[n], wt1[n], bt0[n], tat0[n], wt0[n], priority[n], wtavg = 0, tatavg = 0;
    printf("Enter priority (0 for user, 1 for system):\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &priority[i]);
    }
    int sys = 0, user = 0;
    printf("Enter burst time of each process:\n");
    for (int i = 0; i < n; i++)
    {
        if (priority[i] == 0)
        {
            scanf("%d", &bt0[user]);
            user++;
        }
        else
        {
            scanf("%d", &bt1[sys]);
            sys++;
        }
    }
    if (sys > 0)
    {
        wt1[0] = 0;
        tat1[0] = bt1[0];
        for (int i = 1; i < sys; i++)
        {
            wt1[i] = wt1[i - 1] + bt1[i - 1];
            tat1[i] = tat1[i - 1] + bt1[i];
        }
    }
    if (user > 0)
    {
        wt0[0] = sys > 0 ? wt1[sys - 1] + bt1[sys - 1] : 0;
        tat0[0] = bt0[0] + wt0[0];
        for (int i = 1; i < user; i++)
        {
            wt0[i] = wt0[i - 1] + bt0[i - 1];
            tat0[i] = tat0[i - 1] + bt0[i];
        }
    }
    for (int i = 0; i < sys; i++)
    {
        wtavg += wt1[i];
        tatavg += tat1[i];
    }
    for (int i = 0; i < user; i++)
    {
        wtavg += wt0[i];
        tatavg += tat0[i];
    }
    printf("\nAverage turnaround time: %.2f\n", (float)tatavg / n);
    printf("Average waiting time: %.2f\n", (float)wtavg / n);
    return 0;
}
